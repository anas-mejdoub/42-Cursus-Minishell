/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:59:13 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 16:25:58 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*fetch_paths(char **paths, char *command)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	while (paths[i])
	{
		tmp = ft_freed_join(paths[i], "/");
		tmp2 = ft_freed_join(tmp, command);
		if (!access(tmp2, F_OK) && access(tmp2, X_OK) == -1)
		{
			ft_putstr_fd("minishell : Permission denied\n", 2);
			exit(126);
		}
		if (!access(tmp2, F_OK))
			return (tmp2);
		i++;
		free(tmp2);
		tmp2 = NULL;
	}
	return (NULL);
}

char	*get_path(char *command, t_env *env)
{
	char	**paths;
	char	*tmp;

	paths = NULL;
	if (!command[0])
		return (NULL);
	if (env)
		paths = ft_split(env->get(env->data, "PATH"), ':');
	if (!paths)
	{
		if (!access(command, F_OK))
			return (command);
		return (NULL);
	}
	tmp = fetch_paths(paths, command);
	if (tmp)
		return (tmp);
	if (!access(command, F_OK) && access(command, X_OK) == -1)
		print_err_exit(2, 126, "minishell : Permission denied\n");
	if (!access(command, F_OK) && ((command[0] == '.' && command[1])
			|| command[0] == '/'))
		return (command);
	return (0);
}

char	**commands_args_helper(char *tmp_str, t_command_args *args, char **res)
{
	char	**tmp_arr;
	int		i;

	i = 0;
	if (ft_strchr(tmp_str, ' ') && (args->env || args->wildcard))
	{
		tmp_arr = ft_split(tmp_str, ' ');
		i = 0;
		while (tmp_arr[i])
		{
			res = add_to_args(res, tmp_arr[i]);
			i++;
		}
	}
	else
		res = add_to_args(res, tmp_str);
	return (res);
}

char	**get_command_args(t_command_args *a, t_env *env)
{
	char	**res;
	char	*tmp_str;
	bool	exp;

	res = NULL;
	exp = false;
	if (!a)
		return (NULL);
	if (!ft_strncmp(a->content, "export", ft_strlen(a->content))
		&& ft_strlen(a->content) == 6)
		exp = true;
	while (a)
	{
		tmp_str = env_expander(a->content, a->index_list, env, a->wildcard);
		if (args_help(&a, tmp_str))
			continue ;
		if (exp)
			res = add_to_args(res, tmp_str);
		else
			res = commands_args_helper(tmp_str, a, res);
		a = a->next;
	}
	return (res);
}

bool	get_files(t_command *command, t_env *env, bool *found_in)
{
	if (command->in_files)
	{
		command->infd = open_in_files(command->in_files, env);
		if (command->infd < 0)
		{
			*found_in = true;
			g_var = 1;
			return (false);
		}
	}
	if (command->outfiles && !*found_in)
	{
		command->outfd = open_out_files(command->outfiles, env);
		if (command->outfd < 0)
		{
			g_var = 1;
			return (false);
		}
	}
	return (true);
}

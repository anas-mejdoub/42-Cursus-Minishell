/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:35:02 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 12:40:44 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

static void	print_all_envs(t_env *env)
{
	t_env_data	*tmp_env_data;
	int			k;

	tmp_env_data = env->data;
	while (tmp_env_data)
	{
		printf("declare -x %s", tmp_env_data->key);
		if (tmp_env_data->value)
		{
			printf("=\"");
			k = 0;
			while (tmp_env_data->value[k])
			{
				if (tmp_env_data->value[k] == '\"'
					|| tmp_env_data->value[k] == '$')
					printf("\\");
				printf("%c", tmp_env_data->value[k]);
				k++;
			}
			printf("\"");
		}
		printf("\n");
		tmp_env_data = tmp_env_data->next;
	}
}

static int	change_var(char **arr, t_env *env, int *i, int *j)
{
	char	*key;
	char	*value;
	int		len;

	if (arr[(*i)][(*j)] == '\0')
	{
		len = (*j);
		key = ft_substr(arr[(*i)], 0, len);
		env->set(&env->data, key, NULL);
		(*i)++;
		return (1);
	}
	if (arr[(*i)][(*j)] != '=')
		return (print_err(4, 1, "minishell: export: `", arr[(*i)],
				"': not a valid identifier\n"), (*i)++, -1);
	else if (arr[(*i)][(*j)] == '=')
	{
		len = (*j);
		key = ft_substr(arr[(*i)], 0, len);
		value = ft_substr(arr[(*i)] + len + 1, 0, ft_strlen(arr[(*i)] + len
					+ 1));
		env->set(&env->data, key, value);
	}
	return (0);
}

static int	modify_var(t_command *cmd, t_env *env, int *i)
{
	int	j;
	int	ret;
	int	a;

	j = 0;
	ret = 0;
	a = 0;
	if (ft_isalpha(cmd->args[(*i)][j]) || cmd->args[(*i)][j] == '_')
	{
		while (cmd->args[(*i)][j] && (ft_isalnum(cmd->args[(*i)][j])
				|| cmd->args[(*i)][j] == '_'))
			j++;
		a = change_var(cmd->args, env, i, &j);
		if (a == -1 || a == 1)
			return (a);
	}
	else
	{
		print_err(4, 1, "minishell: export: `", cmd->args[(*i)],
			"': not a valid identifier\n");
		ret = -1;
		(*i)++;
		return (-1);
	}
	return (0);
}

static int	export_it(t_command *cmd, t_env *env)
{
	int	i;
	int	ret;
	int	a;

	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		a = modify_var(cmd, env, &i);
		if (a == 1 || a == -1)
		{
			if (a == -1)
				ret = -1;
			continue ;
		}
		i++;
	}
	if (i == 1)
		print_all_envs(env);
	return (ret);
}

int	export_cmd(t_command *cmd, t_env *env)
{
	int	ret;
	int	fd_in;
	int	fd_out;

	ret = 0;
	if (!env)
		return (0);
	if (cmd->args && !(!ft_strncmp(cmd->args[0], "export",
				ft_strlen(cmd->args[0]))
			&& ft_strlen(cmd->args[0]) == ft_strlen("export")))
		return (-1);
	if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	ret = export_it(cmd, env);
	if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	return (ret);
}

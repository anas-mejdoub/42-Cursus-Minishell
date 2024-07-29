/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:33:22 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 07:58:05 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

static char	*working_dir(void)
{
	char	tmp[1024];
	char	*ptr;

	ptr = getcwd(tmp, 1024);
	if (!ptr)
		print_err(3, 1, strerror(errno), "\n");
	return (ptr);
}

static void	update_env(t_env *env, char *oldpwd)
{
	char	*ptr;

	ptr = working_dir();
	if (env->get(env->data, "OLDPWD"))
		env->set(&env->data, "OLDPWD", oldpwd);
	if (env->get(env->data, "PWD"))
		env->set(&env->data, "PWD", ptr);
}

static int	change_dir(t_env *env, t_command *cmd, int *fd_in, int *fd_out)
{
	char	*pwd;
	char	*path;

	pwd = env->get(env->data, "PWD");
	if (cmd->args[1] == NULL)
		path = env->get(env->data, "HOME");
	else
		path = cmd->args[1];
	if (!path && cmd->args[1] == NULL)
	{
		print_err(2, 1, "minishell: cd: HOME not set\n");
		return (restor_rediraction(cmd, fd_in, fd_out), -1);
	}
	if (chdir(path) == -1)
	{
		print_err(3, 1, strerror(errno), "\n");
		return (restor_rediraction(cmd, fd_in, fd_out), -1);
	}
	return (0);
}

int	cd_cmd(t_command *cmd, t_env *env)
{
	char	*oldpwd;
	int		fd_in;
	int		fd_out;

	if (!env)
		return (0);
	if (cmd->args && !(!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))
			&& ft_strlen(cmd->args[0]) == ft_strlen("cd")))
		return (-1);
	if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	oldpwd = working_dir();
	if (change_dir(env, cmd, &fd_in, &fd_out) == -1)
		return (-1);
	update_env(env, oldpwd);
	if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	return (0);
}

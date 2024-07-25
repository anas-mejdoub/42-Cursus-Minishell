/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:27:05 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 19:06:30 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

static bool	compare(char *cmd, char *ptr)
{
	size_t	len;

	len = ft_strlen(cmd);
	return ((!ft_strncmp(cmd, ptr, len) && len == ft_strlen(ptr)));
}

int	is_builtin(t_command *cmd)
{
	if (!cmd->command_arg)
		return (0);
	if (compare(cmd->command_arg->content, "export"))
		return (1);
	else if (compare(cmd->command_arg->content, "env"))
		return (1);
	else if (compare(cmd->command_arg->content, "echo"))
		return (1);
	else if (compare(cmd->command_arg->content, "exit"))
		return (1);
	else if (compare(cmd->command_arg->content, "cd"))
		return (1);
	else if (compare(cmd->command_arg->content, "pwd"))
		return (1);
	else if (compare(cmd->command_arg->content, "unset"))
		return (1);
	return (0);
}

static int	do_builtin_helper(t_command *cmd, t_env *env)
{
	if (compare(cmd->args[0], "exit"))
	{
		if (exit_comand(cmd) == -1)
			return (-1);
		return (1);
	}
	else if (compare(cmd->args[0], "cd"))
	{
		if (cd_cmd(cmd, env) == -1)
			return (-1);
		return (1);
	}
	else if (compare(cmd->args[0], "pwd"))
	{
		if (pwd_cmd(cmd) == -1)
			return (-1);
		return (1);
	}
	else if (compare(cmd->args[0], "unset"))
	{
		if (unset_cmd(cmd, env) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int	do_builtin(t_command *cmd, t_env *env)
{
	if (compare(cmd->args[0], "export"))
	{
		if (export_cmd(cmd, env) == -1)
			return (-1);
		return (1);
	}
	else if (compare(cmd->args[0], "env"))
	{
		if (env_cmd(cmd, env) == -1)
			return (-1);
		return (1);
	}
	else if (compare(cmd->args[0], "echo"))
	{
		if (echo_cmd(cmd) == -1)
			return (-1);
		return (1);
	}
	else
		return (do_builtin_helper(cmd, env));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:39 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 16:25:51 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>

t_exec_ret	*single_built(t_command *cmd, t_exec_ret *ret, bool f, t_env *env)
{
	if ((cmd->outfiles && cmd->outfd == -1) || (cmd->infd && f == true)
		|| do_builtin(cmd, env) == -1)
	{
		g_var = 1;
	}
	else
		g_var = 0;
	ret->ret = -1;
	return (ret);
}

t_exec_ret	*executor(t_command *command, t_env *env, char c)
{
	int			fd[2];
	t_exec_ret	*ret;

	fd[0] = -1;
	fd[1] = -1;
	ret = ft_alloc(sizeof(t_exec_ret), NULL, MALLOC);
	ret->pids = NULL;
	ret->ret = -1;
	if (!command)
		return (ret);
	if (command->type_node == AND_NODE)
		return (and_node(command, ret, env));
	if (command->type_node == OR_NODE)
		return (or_node(command, ret, env));
	if (command->type_node == PIPE_LINE_NODE || command->type_node == ROOT_NODE)
	{
		if (!pipeline_node(&command, ret, env))
			return (NULL);
	}
	else if (command->type_node == SUBSHELL_NODE)
		return (subshell_node(command, ret, env, c));
	else if (command->type_node == NODE)
		return (cmd_node(command, ret, env, c));
	return (ret);
}

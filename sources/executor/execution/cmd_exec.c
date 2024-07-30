/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:10:01 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/30 09:34:55 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	parent_proc(t_command *command, t_exec_ret *ret, char c, int i)
{
	v_close_fd(2, command->infd, command->outfd);
	if (c == 'r')
		v_close_fd(2, command->outfd, command->fd[1]);
	if (c == 'l')
		v_close_fd(2, command->infd, command->fd[0]);
	ret->ret = i;
	ret->pids = NULL;
}

bool	builtin_condition(t_command *command, t_env *env, bool f)
{
	if ((command->outfiles && command->outfd == -1) || (command->infd
			&& f == true) || do_builtin(command, env) == -1)
		return (true);
	return (false);
}

void	exec_cmd_nf(char *str)
{
	print_err_exit(4, 127, "minishell: ", str, ": command not found\n");
}

void	child_proc(t_command *command, char c, bool f, t_env *env)
{
	if (command->command_arg && command->args && command->args[0])
		command->path = get_path(command->args[0], env);
	if ((command->outfiles && command->outfd == -1) || (command->infd
			&& f == true))
		exit(1);
	if (command->command_arg && !command->path && !is_builtin(command)
		&& command->args && command->args[0] && access(command->args[0], F_OK))
		exec_cmd_nf(command->args[0]);
	if (!command->path && !is_builtin(command) && command->command_arg
		&& command->args && command->args[0] && !access(command->args[0], F_OK)
		&& access(command->args[0], X_OK))
		print_err_exit(2, 126, "minishell :  Permission denied\n");
	duping(command);
	right_left(command, c);
	v_close_fd(2, command->outfd, command->infd);
	if (!command->path && !command->args)
		exit(0);
	if (is_builtin(command))
	{
		if (builtin_condition(command, env, f))
			exit(1);
		exit(0);
	}
	if (execve(command->path, command->args, env_to_2d_arr(env)) == -1)
		exec_cmd_nf(command->args[0]);
}

bool	args_help(t_command_args **a, char *tmp_str)
{
	if (tmp_str == NULL)
	{
		*a = (*a)->next;
		return (true);
	}
	if (tmp_str[0] == '\0' && (*a)->index_list && !(*a)->including_null)
	{
		*a = (*a)->next;
		return (true);
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:13:02 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 16:25:14 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	duping(t_command *command)
{
	if (command->outfd != -1)
	{
		dup2(command->outfd, STDOUT_FILENO);
		command->dup = true;
	}
	if (command->infd != -1)
	{
		command->dup = true;
		dup2(command->infd, STDIN_FILENO);
	}
}

void	right_left(t_command *command, char c)
{
	if (c == 'r')
	{
		close(command->fd[0]);
		if (command->to_close != NULL)
			close_fds(command->to_close);
	}
	if (c == 'l')
	{
		if (command->to_close != NULL)
			close_fds(command->to_close);
		close(command->fd[1]);
	}
}

void	waiting_pids(t_exec_ret *ret)
{
	int	status;
	int	eter;

	eter = 0;
	status = 0;
	while (1)
	{
		if (ret->pids[eter] == -1)
			break ;
		waitpid(ret->pids[eter], &status, 0);
		if (WIFEXITED(status))
			g_var = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_var = WTERMSIG(status) + 128;
		eter++;
	}
}

void	wait_one(t_exec_ret *ret)
{
	int	status;

	status = 0;
	waitpid(ret->ret, &status, 0);
	if (WIFEXITED(status))
		g_var = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_var = WTERMSIG(status) + 128;
	ret->pids = add_int(ret->pids, ret->ret);
}

bool	get_files_args(t_command *command, t_env *env, bool *found_in)
{
	command->args = get_command_args(command->command_arg, env);
	if (command->in_files)
	{
		command->infd = open_in_files(command->in_files, env);
		if (command->infd < 0)
		{
			*found_in = true;
			g_var = 1;
		}
	}
	if (command->outfiles && !*found_in)
	{
		command->outfd = open_out_files(command->outfiles, env);
		if (command->outfd < 0)
			g_var = 1;
	}
	if (command->args == NULL)
		return (true);
	return (true);
}

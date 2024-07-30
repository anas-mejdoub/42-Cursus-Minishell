/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:08:23 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/30 11:24:15 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	subshell_childp(t_command *command, t_exec_ret *ret, t_env *env, char c)
{
	int	kk;

	kk = 0;
	ret = executor(command->right, env, 'r');
	if (ret && ret->pids)
		waiting_pids(ret);
	else if (ret && ret->ret != -1)
	{
		waitpid(ret->ret, &kk, 0);
		if (WIFEXITED(kk))
			g_var = WEXITSTATUS(kk);
		else if (WIFSIGNALED(kk))
			g_var = WTERMSIG(kk) + 128;
	}
	close_fds(((t_command *)command)->to_close);
	close_fds(((t_command *)command->right)->to_close);
	if (c == 'r')
		v_close_fd(2, command->fd[1], ((t_command *)command->right)->fd[1]);
	if (c == 'l')
		v_close_fd(2, command->fd[0], ((t_command *)command->right)->fd[0]);
	v_close_fd(4, command->outfd, command->infd,
		((t_command *)command->right)->outfd,
		((t_command *)command->right)->infd);
	exit(g_var);
}

void	subshell_parentp(t_command *command, t_exec_ret *ret, int f, char c)
{
	int	status;

	status = 0;
	if (!c)
		v_close_fd(4, command->outfd, command->infd,
			((t_command *)command->right)->outfd,
			((t_command *)command->right)->infd);
	if (c == 'r')
		v_close_fd(4, ((t_command *)command->right)->outfd, command->outfd,
			command->fd[1], ((t_command *)command->right)->fd[1]);
	if (c == 'l')
		v_close_fd(4, command->fd[0], command->infd,
			((t_command *)command->right)->fd[0],
			((t_command *)command->right)->infd);
	g_var = WEXITSTATUS(status);
	ret->ret = f;
	ret->pids = NULL;
}

void	subshell_config(t_command *command, char c)
{
	if (c == 'r')
		command->to_close = add_int(command->to_close, command->fd[0]);
	if (command->outfd != -1)
		((t_command *)command->right)->outfd = command->outfd;
	if (command->infd != -1)
		((t_command *)command->right)->infd = command->infd;
}

void	child_sub_caller(t_command *command, t_exec_ret *ret, t_env *env,
		char c)
{
	signal(SIGINT, SIG_DFL);
	if (command->to_close)
		close_fds(command->to_close);
	subshell_childp(command, ret, env, c);
}

t_exec_ret	*subshell_node(t_command *command, t_exec_ret *ret, t_env *env,
		char c)
{
	bool	found_in;
	int		f;

	found_in = false;
	if (c == 'r')
		((t_command *)command->right)->to_close = add_int(command->to_close,
				command->fd[0]);
	((t_command *)command->right)->fd[0] = command->fd[0];
	((t_command *)command->right)->fd[1] = command->fd[1];
	if (!get_files(command, env, &found_in))
		return (NULL);
	subshell_config(command, c);
	signal(SIGINT, SIG_IGN);
	f = fork();
	if (f == 0)
		child_sub_caller(command, ret, env, c);
	else if (f > 0)
		subshell_parentp(command, ret, f, c);
	if (f < 0)
		return (print_err(2, 1,
				"minishell fork : Resource temporarily unavailable\n"), NULL);
	return (ret);
}

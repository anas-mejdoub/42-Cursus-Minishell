/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:06:20 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 11:50:39 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

bool	if_pipeline(t_command **command, int fd[2])
{
	int	k;

	((t_command *)(*command)->left)->to_close = add_int((*command)->to_close,
			(*command)->fd[0]);
	((t_command *)(*command)->right)->to_close = add_int((*command)->to_close,
			(*command)->fd[0]);
	if ((*command)->outfd != -1)
		((t_command *)(*command)->left)->outfd = (*command)->outfd;
	if ((*command)->infd != -1)
		((t_command *)(*command)->right)->infd = (*command)->infd;
	k = pipe(fd);
	((t_command *)(*command)->left)->fd[0] = fd[0];
	((t_command *)(*command)->left)->fd[1] = fd[1];
	((t_command *)(*command)->right)->fd[0] = fd[0];
	((t_command *)(*command)->right)->fd[1] = fd[1];
	if (k == -1)
		return (v_close_fd(2, fd[1]), print_err(2, 1,
				"minishell fork : Resource temporarily unavailable\n"), false);
	((t_command *)(*command)->right)->outfd = fd[1];
	((t_command *)(*command)->left)->infd = fd[0];
	return (true);
}

void	init_vars(int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
}

bool	pipeline_node(t_command **command, t_exec_ret *ret, t_env *env)
{
	int			fd[2];
	t_exec_ret	*tmp;

	tmp = NULL;
	init_vars(fd);
	if ((*command)->type_node == PIPE_LINE_NODE && !if_pipeline(command, fd))
		return (false);
	if ((*command) && (*command)->right && is_builtin((*command)->right)
		&& !(*command)->left)
		tmp = executor((*command)->right, env, 'b');
	else if ((*command) && (*command)->right)
		tmp = executor((*command)->right, env, 'r');
	close(fd[1]);
	if (!tmp)
		return (v_close_fd(2, fd[1], fd[0]), false);
	if (tmp && tmp->pids)
		ret->pids = tmp->pids;
	else if (tmp && tmp->ret != -1)
		ret->pids = add_int(ret->pids, tmp->ret);
	tmp = executor((*command)->left, env, 'l');
	close(fd[0]);
	if (!tmp)
		return (v_close_fd(2, fd[1], fd[0]), false);
	ret->pids = add_int(ret->pids, tmp->ret);
	return (true);
}

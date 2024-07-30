/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:02:56 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/30 09:50:13 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	handle_intr_sig(int sig)
{
	(void)sig;
}

t_exec_ret	*cmd_node(t_command *command, t_exec_ret *ret, t_env *env,
		char c)
{
	bool	found_in;
	pid_t	i;

	found_in = false;
	if (!get_files_args(command, env, &found_in))
		return (NULL);
	if (c == 'b')
		return (single_built(command, ret, found_in, env));
	signal(SIGINT, SIG_IGN);
	g_var = 0;
	i = fork();
	if (i < 0)
	{
		print_err(2, 1, "minishell fork : Resource temporarily unavailable\n");
		return (NULL);
	}
	signal(SIGINT, handle_intr_sig);
	if (i == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		child_proc(command, c, found_in, env);
	}
	else if (i > 0)
		parent_proc(command, ret, c, i);
	return (ret);
}

t_exec_ret	*and_node(t_command *command, t_exec_ret *ret,
		t_env *env)
{
	t_exec_ret	*tmp;
	char		c;

	tmp = NULL;
	share_fds(command);
	c = '\0';
	if (is_builtin(command->right))
		c = 'b';
	tmp = executor(command->right, env, c);
	if (tmp && tmp->pids)
	{
		waiting_pids(tmp);
		ret->pids = tmp->pids;
	}
	else if (tmp && tmp->ret != -1)
		wait_one(tmp);
	if (g_var == 0)
		second_cmd(command, ret, env);
	else
		return (NULL);
	return (ret);
}

t_exec_ret	*or_node(t_command *command, t_exec_ret *ret, t_env *env)
{
	t_exec_ret	*tmp;
	char		c;

	tmp = NULL;
	share_fds(command);
	c = '\0';
	if (is_builtin(command->right))
		c = 'b';
	tmp = executor(command->right, env, c);
	if (tmp && tmp->pids)
	{
		waiting_pids(tmp);
		ret->pids = tmp->pids;
	}
	else if (tmp && tmp->ret != -1)
		wait_one(tmp);
	if (g_var != 0)
		second_cmd(command, ret, env);
	else
		return (NULL);
	return (ret);
}

bool	second_cmd(t_command *cmd, t_exec_ret *ret, t_env *env)
{
	t_exec_ret	*tmp;
	char		c;

	c = '\0';
	tmp = NULL;
	if (is_builtin(cmd->left))
		c = 'b';
	tmp = executor(cmd->left, env, c);
	if (!tmp)
		return (false);
	if (tmp && tmp->pids)
		ret->pids = tmp->pids;
	else if (tmp && tmp->ret != -1)
		ret->pids = add_int(ret->pids, tmp->ret);
	return (true);
}

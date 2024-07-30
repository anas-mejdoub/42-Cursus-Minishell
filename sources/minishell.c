/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:59:33 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/30 11:11:10 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tchbi7a(void)
{
	printf(RED "██████  ██░ ██ ▓█████  ██▓     ██▓            \n" \
			"▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒            \n" \
			"░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░            \n" \
			"  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░            \n" \
			"▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒        \n" \
			"▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░        \n" \
			"░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░        \n" \
			"░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░           \n" \
			"      ░   ░  ░  ░   ░  ░    ░  ░    ░  ░        \n" RESET);
}

static void	wait_commands(t_exec_ret	*r)
{
	int			i;
	int			status;

	i = 0;
	while (r && r->pids)
	{
		if (r->pids[i] == -1)
			break ;
		waitpid(r->pids[i], &status, 0);
		if (WIFEXITED(status))
			g_var = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_var = WTERMSIG(status) + 128;
		i++;
	}
}

static void	minishell(t_env *env)
{
	t_elem		*elem;
	t_command	*root;
	t_exec_ret	*r;

	while (1)
	{
		elem = lexer();
		if (!elem)
		{
			ft_alloc(0, NULL, FREE_ALL);
			continue ;
		}
		root = parser(elem, env);
		r = executor(root, env, '\0');
		if (!r || !r->pids)
		{
			ft_alloc(0, NULL, FREE_ALL);
			continue ;
		}
		wait_commands(r);
		ft_alloc(0, NULL, FREE_ALL);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_env		*env;

	(void)ac;
	(void)av;
	print_tchbi7a();
	env = init_env(ev);
	minishell(env);
	return (g_var);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 07:45:19 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

// void	new_prompt(int sig)
// {
// 	(void)sig;
// 	globalVar = 1;
// 	printf(BHMAG "\n" RESET);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

t_elem	*subshell_syntax(t_elem *elem)
{
    print_err(2, 2, "synthax error : missing a parenthese symbole\n");
    free_elem(elem);
	return (NULL);
}

t_elem	*lexer(void)
{
	int		subshell;
	t_elem	*elem;
	char	*line;
	t_list	*list;

	subshell = 0;
	elem = NULL;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	rl_on_new_line();
	line = readline(BHMAG "➜ minishell$ " RESET);
	if (line == NULL)
		exit(globalVar);
	if (line && *line)
	{
		add_history(line);
		if (!tokenize(line, &subshell, &elem))
			return (NULL);
		free(line);
	}
	if (subshell != 0)
        return (subshell_syntax(elem));
	list = syntax_error(elem);
	if (list)
        return(check_syntax_error(list, elem));
	return (elem);
}

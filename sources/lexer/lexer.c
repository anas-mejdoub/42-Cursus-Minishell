/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 07:53:50 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"


static t_elem *check_errors(t_elem *elem, int subshell, t_list *list)
{
	if (subshell != 0)
	{
		print_err(2, 2, "synthax error : missing a parenthese symbole\n");
    	free_elem(elem);
		return (NULL);
	}
        // return (subshell_syntax(elem));
	list = syntax_error(elem);
	if (list)
        return(check_syntax_error(list, elem));
	return (elem);
}

// t_elem	*subshell_syntax(t_elem *elem)
// {
//     print_err(2, 2, "synthax error : missing a parenthese symbole\n");
//     free_elem(elem);
// 	return (NULL);
// }

t_elem	*lexer(void)
{
	int		subshell;
	t_elem	*elem;
	char	*line;
	t_list	*list;

	subshell = 0;
	elem = NULL;
	list = NULL;
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
	// if (subshell != 0)
    //     return (subshell_syntax(elem));
	// list = syntax_error(elem);
	// if (list)
    //     return(check_syntax_error(list, elem));
	// return (elem);
	return (check_errors(elem, subshell, list));
}

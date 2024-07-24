/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 07:36:43 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"


// t_elem	*tokenize(char *line, int *subshell, t_elem **elem)
// {
// 	int		i;

// 	i = 0;
// 	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
// 		i++;
// 	while (line[i])
// 	{
// 		if (line[i] && line[i] == QOUTE)
// 		{
// 			if (qoute_handler(elem, line, &i))
// 				return (free(*elem), NULL);
// 		}
// 		else if (line[i] && line[i] == DOUBLE_QUOTE)
// 		{
// 			if (double_qoute_handler(elem, line, &i))
// 				return (free(*elem), NULL);
// 		}
// 		else if (line[i])
// 		{
// 			if (general_handler(elem, line, &i, subshell))
// 				return (free(*elem), NULL);
// 		}
// 	}
// 	return (*elem);
// }

void	handle_sigint(int sig)
{
	(void)sig;
	globalVar = 1;
	printf(BHMAG "\n" RESET);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

// t_elem	*check_syntax_error(t_list	*list, t_elem *elem)
// {
//     char *str;

//     str = NULL;
//     print_err(2, 2, "minishell: syntax error\n");
// 	list = list->next;
// 	while (list)
// 	{
// 		str = here_doc(list->content);
// 		free(str);
// 		list = list->next;
// 	}
//     free_elem(elem);
// 	return (NULL);
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
	signal(SIGINT, handle_sigint);
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

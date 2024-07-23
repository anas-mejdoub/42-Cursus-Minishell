/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/23 13:15:45 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

int	is_token(char c)
{
	if (c != WHITE_SPACE && c != '\t' && c != NEW_LINE && c != QOUTE
		&& c != DOUBLE_QUOTE && c != ENV && c != PIPE_LINE && c != REDIR_IN
		&& c != REDIR_OUT && c != START_SUBSHELL && c != END_SUBSHELL
		&& c != WILDCARD)
		return (1);
	return (0);
}

int	env_handeler(t_elem **elem, char *line, int *i, int state)
{
	int	current_index;

	(*i)++;
	current_index = (*i);
	if (line[(*i)] == '?')
	{
		(*i)++;
		if (allocate_node(elem, ft_substr(line, current_index - 1, (*i)
					- current_index + 1), state, ENV))
			return (1);
	}
	else if (ft_isalpha(line[(*i)]) || line[(*i)] == '_')
	{
		while (line[(*i)] && (ft_isalnum(line[(*i)]) || line[(*i)] == '_'))
			(*i)++;
		if ((*i) != current_index)
		{
			if (allocate_node(elem, ft_substr(line, current_index - 1, (*i)
						- current_index + 1), state, ENV))
				return (1);
		}
	}
	return (0);
}

int	qoute_handler(t_elem **elem, char *line, int *i)
{
	int	current_index;

	if (line[(*i)] == QOUTE)
	{
		if (allocate_node(elem, ft_strdup("\'"), GENERAL, QOUTE))
			return (1);
		(*i)++;
		current_index = (*i);
	}
	while (line[(*i)] && line[(*i)] != QOUTE)
	{
		while (line[(*i)] && line[(*i)] != QOUTE)
			(*i)++;
		;
		if (allocate_node(elem, ft_substr(line, current_index, (*i)
					- current_index), IN_QUOTE, WORD))
			return (1);
	}
	if (line[(*i)] == QOUTE)
	{
		if (allocate_node(elem, ft_strdup("\'"), GENERAL, QOUTE))
			return (1);
		(*i)++;
		return (0);
	}
	else
        return (print_err(2, 2,"synthax error : missing a quote\n"), 1);

}

int	double_qoute_handler(t_elem **elem, char *line, int *i)
{
	int	current_index;

	if (line[(*i)] == DOUBLE_QUOTE)
	{
		if (allocate_node(elem, ft_strdup("\""), GENERAL, DOUBLE_QUOTE))
			return (1);
		(*i)++;
		current_index = (*i);
	}
	while (line[(*i)] && line[(*i)] != DOUBLE_QUOTE)
	{
		while (line[(*i)] && line[(*i)] != DOUBLE_QUOTE && !(line[(*i)] == ENV
				&& (ft_isalpha(line[(*i) + 1]) || line[(*i) + 1] == '_'
					|| line[(*i) + 1] == '?')))
			(*i)++;
		if ((*i) != current_index)
		{
			if (allocate_node(elem, ft_substr(line, current_index, (*i)
						- current_index), IN_DQUOTE, WORD))
				return (1);
		}
		if (line[(*i)] == ENV && (ft_isalpha(line[(*i) + 1]) || line[(*i)
				+ 1] == '_' || line[(*i) + 1] == '?'))
		{
			if (env_handeler(elem, line, i, IN_DQUOTE))
				return (1);
		}
		current_index = (*i);
	}
	if (line[(*i)] == DOUBLE_QUOTE)
	{
		if (allocate_node(elem, ft_strdup("\""), GENERAL, DOUBLE_QUOTE))
			return (1);
		(*i)++;
		return (0);
	}
	else
        return (print_err(2, 2,"synthax error : missing a double quote\n"), 1);
}

// int	general_tokens(char *line, t_elem **elem, int *i, int *subshell)
// {
// 	char	*content;

// 	content = NULL;
// 	if (line[(*i)] == WHITE_SPACE || line[(*i)] == '\t'
// 		|| line[(*i)] == NEW_LINE || line[(*i)] == PIPE_LINE
// 		|| line[(*i)] == REDIR_IN || line[(*i)] == REDIR_OUT
// 		|| line[(*i)] == START_SUBSHELL || line[(*i)] == END_SUBSHELL
// 		|| line[(*i)] == WILDCARD || line[(*i)] == '&')
// 	{
// 		if (line[(*i)] == START_SUBSHELL)
// 			(*subshell)++;
// 		if (line[(*i)] == END_SUBSHELL)
// 			(*subshell)--;
// 		if (line[(*i)] == PIPE_LINE && line[(*i) + 1] == PIPE_LINE)
// 		{
// 			allocate_node(elem, ft_strdup("||"), GENERAL, OR);
// 			(*i) += 2;
// 		}
// 		else if (line[(*i)] == REDIR_OUT && line[(*i) + 1] == REDIR_OUT)
// 		{
// 			allocate_node(elem, ft_strdup(">>"), GENERAL, DREDIR_OUT);
// 			(*i) += 2;
// 		}
// 		else if (line[(*i)] == '&' && line[(*i) + 1] == '&')
// 		{
// 			allocate_node(elem, ft_strdup("&&"), GENERAL, AND);
// 			(*i) += 2;
// 		}
// 		else if (line[(*i)] == '<' && line[(*i) + 1] == '<')
// 		{
// 			allocate_node(elem, ft_strdup("<<"), GENERAL, HERE_DOC);
// 			(*i) += 2;
// 		}
// 		else if (line[(*i)] == '\t')
// 		{
// 			allocate_node(elem, ft_strdup(" "), GENERAL, WHITE_SPACE);
// 			(*i)++;
// 		}
// 		else if (line[(*i)] != '&')
// 		{
// 			content = ft_calloc(2, 1);
// 			content[0] = line[(*i)];
// 			allocate_node(elem, content, GENERAL, (int)line[(*i)]);
// 			(*i)++;
// 		}
// 	}
// 	return (0);
// }

int	general_handler(t_elem **elem, char *line, int *i, int *subshell)
{
	int	current_index;

	current_index = (*i);
	while (line[(*i)] && (line[(*i)] != QOUTE && line[(*i)] != DOUBLE_QUOTE))
	{
		while (((line[(*i)] && (is_token(line[(*i)]) && !(line[(*i)] == '&'
							&& line[(*i) + 1] == '&'))) || (line[(*i)] == ENV
					&& !ft_isalpha(line[(*i) + 1]) && line[(*i) + 1] != '_'
					&& line[(*i) + 1] != '?')))
			(*i)++;
		if (current_index != (*i))
		{
			if (allocate_node(elem, ft_substr(line, current_index, (*i)
						- current_index), GENERAL, WORD))
				return (1);
			current_index = (*i);
		}
		if (line[(*i)] == ENV && (ft_isalpha(line[(*i) + 1]) || line[(*i)
				+ 1] == '_' || line[(*i) + 1] == '?'))
		{
			if (env_handeler(elem, line, i, GENERAL))
				return (1);
		}
		else if (general_tokens(line, elem, i, subshell))
			return (1);
		current_index = (*i);
	}
	return (0);
}

t_elem	*tokenize(char *line, int *subshell, t_elem **elem)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i])
	{
		if (line[i] && line[i] == QOUTE)
		{
			if (qoute_handler(elem, line, &i))
				return (free(*elem), NULL);
		}
		else if (line[i] && line[i] == DOUBLE_QUOTE)
		{
			if (double_qoute_handler(elem, line, &i))
				return (free(*elem), NULL);
		}
		else if (line[i])
		{
			if (general_handler(elem, line, &i, subshell))
				return (free(*elem), NULL);
		}
	}
	return (*elem);
}

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

t_elem	*check_syntax_error(t_list	*list, t_elem *elem)
{
    char *str;

    str = NULL;
    print_err(2, 2, "minishell: syntax error\n");
	list = list->next;
	while (list)
	{
		str = here_doc(list->content);
		free(str);
		list = list->next;
	}
    free_elem(elem);
	return (NULL);
}
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
		tokenize(line, &subshell, &elem);
		free(line);
	}
	if (subshell != 0)
        return (subshell_syntax(elem));
	list = syntax_error(elem);
	if (list)
        return(check_syntax_error(list, elem));
	return (elem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tocken_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:13:10 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/23 16:16:21 by nbenyahy         ###   ########.fr       */
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

static bool	check_tockens(char a, int *subshell)
{
	if (a == START_SUBSHELL)
		(*subshell)++;
	if (a == END_SUBSHELL)
		(*subshell)--;
	return (a == WHITE_SPACE || a == '\t' || a == NEW_LINE || a == PIPE_LINE
		|| a == REDIR_IN || a == REDIR_OUT || a == START_SUBSHELL
		|| a == END_SUBSHELL || a == WILDCARD || a == '&');
}

static int	create_node(t_elem **elem, char type, char *content, int *i)
{
	char	*str;
	int		res;

	str = ft_strdup(content);
	if (!str)
		return (1);
	res = allocate_node(elem, str, GENERAL, type);
	(*i) += ft_strlen(content);
	return (res);
}

int	general_tokens(char *line, t_elem **elem, int *i, int *subshell)
{
	char	*content;

	content = NULL;
	if (check_tockens(line[(*i)], subshell))
	{
		if (line[(*i)] == PIPE_LINE && line[(*i) + 1] == PIPE_LINE)
			create_node(elem, OR, "||", i);
		else if (line[(*i)] == REDIR_OUT && line[(*i) + 1] == REDIR_OUT)
			create_node(elem, DREDIR_OUT, ">>", i);
		else if (line[(*i)] == '&' && line[(*i) + 1] == '&')
			create_node(elem, AND, "&&", i);
		else if (line[(*i)] == '<' && line[(*i) + 1] == '<')
			create_node(elem, HERE_DOC, "<<", i);
		else if (line[(*i)] == '\t')
			create_node(elem, WHITE_SPACE, " ", i);
		else if (line[(*i)] != '&')
		{
			content = ft_calloc(2, 1);
			content[0] = line[(*i)];
			create_node(elem, (int)line[(*i)], content, i);
			free(content);
		}
	}
	return (0);
}

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
			allocate_node(elem, ft_substr(line, current_index, \
							(*i) - current_index), GENERAL, WORD);
			current_index = (*i);
		}
		if (line[(*i)] == ENV && (ft_isalpha(line[(*i) + 1]) || \
			line[(*i) + 1] == '_' || line[(*i) + 1] == '?'))
			env_handeler(elem, line, i, GENERAL);
		else if (general_tokens(line, elem, i, subshell))
			return (1);
		current_index = (*i);
	}
	return (0);
}

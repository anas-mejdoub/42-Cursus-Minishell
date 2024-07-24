/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:08:36 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 07:36:11 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

void	free_elem(t_elem *elem)
{
	t_elem	*prev;

	while (elem)
	{
		prev = elem;
		elem = elem->next;
		free(prev->content);
		free(prev);
	}
}

int	allocate_node(t_elem **elem, char *content, int state, int token)
{
	t_elem	*new_node;
	t_elem	*last_node;

	if (!content || content[0] == '\0')
		return (0);
	new_node = malloc(sizeof(t_elem));
	if (!new_node)
		return (1);
	new_node->state = state;
	new_node->type = token;
	new_node->content = content;
	new_node->len = ft_strlen(content);
	new_node->next = NULL;
	if (!(*elem))
		(*elem) = new_node;
	else
	{
		last_node = *elem;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
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
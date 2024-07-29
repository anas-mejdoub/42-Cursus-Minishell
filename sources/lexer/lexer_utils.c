/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:08:36 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 08:44:00 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

int	allocate_node(t_elem **elem, char *content, int state, int token)
{
	t_elem	*new_node;
	t_elem	*last_node;

	if (!content || content[0] == '\0')
		return (0);
	new_node = ft_alloc(sizeof(t_elem), NULL, MALLOC);
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
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i])
	{
		if (line[i] && line[i] == QOUTE)
		{
			if (qoute_handler(elem, line, &i))
				return (NULL);
		}
		else if (line[i] && line[i] == DOUBLE_QUOTE)
		{
			if (double_qoute_handler(elem, line, &i))
				return (NULL);
		}
		else if (line[i])
		{
			if (general_handler(elem, line, &i, subshell))
				return (NULL);
		}
	}
	return (*elem);
}

t_elem	*check_syntax_error(t_list *list)
{
	char	*str;
	t_list	*tmp;

	str = NULL;
	tmp = list;
	print_err(2, 2, "minishell: syntax error\n");
	tmp = tmp->next;
	while (tmp)
	{
		str = here_doc(tmp->content);
		ft_alloc(0, str, FREE_PTR);
		str = NULL;
		tmp = tmp->next;
	}
	return (NULL);
}

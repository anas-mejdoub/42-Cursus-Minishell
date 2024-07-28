/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dqoute_tocken_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:14:26 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/28 17:17:13 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

static int	create_dqoute_node(t_elem **elem, int *i)
{
	if (allocate_node(elem, ft_strdup("\""), GENERAL, DOUBLE_QUOTE))
		return (1);
	else
		(*i)++;
	return (0);
}

static int	dqoute_content(t_elem **elem, char *line, int *i,
		int *current_index)
{
	while (line[(*i)] && line[(*i)] != DOUBLE_QUOTE)
	{
		while (line[(*i)] && line[(*i)] != DOUBLE_QUOTE && !(line[(*i)] == ENV
				&& (ft_isalpha(line[(*i) + 1]) || line[(*i) + 1] == '_'
					|| line[(*i) + 1] == '?')))
			(*i)++;
		if ((*i) != *current_index)
		{
			if (allocate_node(elem, ft_substr(line, *current_index, (*i)
						- *current_index), IN_DQUOTE, WORD))
				return (1);
		}
		if (line[(*i)] == ENV && (ft_isalpha(line[(*i) + 1]) || \
			line[(*i) + 1] == '_' || line[(*i) + 1] == '?'))
		{
			if (env_handeler(elem, line, i, IN_DQUOTE))
				return (1);
		}
		*current_index = (*i);
	}
	return (0);
}

int	double_qoute_handler(t_elem **elem, char *line, int *i)
{
	int	current_index;

	if (line[(*i)] == DOUBLE_QUOTE)
	{
		if (create_dqoute_node(elem, i))
			return (1);
		current_index = (*i);
	}
	if (dqoute_content(elem, line, i, &current_index))
		return (1);
	if (line[(*i)] == DOUBLE_QUOTE)
	{
		if (create_dqoute_node(elem, i))
			return (1);
		return (0);
	}
	else
		return (print_err(2, 2, "synthax error : missing a double quote\n"), 1);
}

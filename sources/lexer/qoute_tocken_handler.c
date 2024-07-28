/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute_tocken_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:52:16 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/28 17:17:34 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

static int	create_qoute_node(t_elem **elem, int *i)
{
	if (allocate_node(elem, ft_strdup("\'"), GENERAL, QOUTE))
		return (1);
	else
		(*i)++;
	return (0);
}

int	qoute_handler(t_elem **elem, char *line, int *i)
{
	int	current_index;

	if (line[(*i)] == QOUTE)
	{
		if (create_qoute_node(elem, i))
			return (1);
		current_index = (*i);
	}
	while (line[(*i)] && line[(*i)] != QOUTE)
	{
		while (line[(*i)] && line[(*i)] != QOUTE)
			(*i)++;
		if (allocate_node(elem, ft_substr(line, current_index, (*i)
					- current_index), IN_QUOTE, WORD))
			return (1);
	}
	if (line[(*i)] == QOUTE)
	{
		if (create_qoute_node(elem, i))
			return (1);
		return (0);
	}
	else
		return (print_err(2, 2, "synthax error : missing a quote\n"), 1);
}

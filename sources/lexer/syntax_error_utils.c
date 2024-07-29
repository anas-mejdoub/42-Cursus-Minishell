/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:44:37 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 08:44:28 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

static void	add_limiter(t_elem **tmp, t_list **original, t_list **list)
{
	(void)list;

		if ((*tmp) && (*tmp)->type != QOUTE && (*tmp)->type != DOUBLE_QUOTE)
			ft_lstadd_back(original, ft_lstnew(ft_strdup((*tmp)->content)));
		else
			ft_lstadd_back(original, ft_lstnew(ft_strdup("")));
		(*tmp) = (*tmp)->next;
}

static t_list	*here_doc_syntax(t_elem **elem, t_list **list,
		t_list **original)
{
	t_elem	*tmp;

	tmp = *elem;
	if (tmp)
		tmp = tmp->next;
	while (tmp && tmp->type == WHITE_SPACE)
		tmp = tmp->next;
	if (tmp && !(is_red_spliter(tmp->type)))
	{
		if (tmp && (tmp->type == QOUTE || tmp->type == DOUBLE_QUOTE))
		{
			tmp = tmp->next;
			add_limiter(&tmp, original, list);
			*elem = (*elem)->next;
		}
		else if (tmp && (tmp->type == WORD || tmp->type != ENV))
		{
			ft_lstadd_back(original, ft_lstnew(ft_strdup(tmp->content)));
			*elem = (*elem)->next;
		}
	}
	else
		return (*original);
	return (NULL);
}

int	other_syntax(t_elem **elem, t_list **list, t_list **original)
{
	if (*elem && (*elem)->type == HERE_DOC)
	{
		if (here_doc_syntax(elem, list, original) != NULL)
			return (0);
	}
	else if ((*elem) && is_spliter((*elem)->type))
	{
		(*elem) = (*elem)->next;
		while ((*elem) && (*elem)->type == WHITE_SPACE)
			(*elem) = (*elem)->next;
		if (!(*elem) || (!is_redirection((*elem)->type) && (*elem)->type != ENV
				&& (*elem)->type != WORD && !is_qoutes((*elem)->type)
				&& (*elem)->type != START_SUBSHELL))
			return (0);
	}
	else if ((*elem) && is_redirection((*elem)->type))
	{
		(*elem) = (*elem)->next;
		while ((*elem) && (*elem)->type == WHITE_SPACE)
			(*elem) = (*elem)->next;
		if (!(*elem) || ((*elem)->type != WORD && !is_qoutes((*elem)->type)
				&& (*elem)->type != WILDCARD && (*elem)->type != ENV))
			return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:44:37 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 11:29:29 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

static void	add_limiter(t_elem **tmp, t_list **original, t_list **list)
{
	char	*str;
	char	*tmp_str;

	while ((*tmp) && ((*tmp)->type != QOUTE || (*tmp)->type != DOUBLE_QUOTE))
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup((*tmp)->content)));
		(*tmp) = (*tmp)->next;
	}
	str = calloc(2, 1);
	while (list)
	{
		tmp_str = ft_strjoin(str, (*list)->content);
		free(str);
		str = tmp_str;
		*list = (*list)->next;
	}
	ft_lstadd_back(original, ft_lstnew(str));
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
	if (tmp && !(is_redirection(tmp->type) || is_spliter(tmp->type)))
	{
		if (tmp && (tmp->type == QOUTE || tmp->type == DOUBLE_QUOTE))
		{
			tmp = tmp->next;
			add_limiter(&tmp, original, list);
			*elem = (*elem)->next;
		}
		else if (tmp && (tmp->type == WORD || tmp->type != ENV))
		{
			ft_lstadd_back(original, ft_lstnew(tmp->content));
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
        if (!(*elem) || (!is_redirection((*elem)->type) && !is_spliter((*elem)->type) 
            && (*elem)->type != DOUBLE_QUOTE && (*elem)->type != QOUTE 
            && (*elem)->type != START_SUBSHELL && (*elem)->type != WORD 
            && (*elem)->type != ENV))
		// if (!(*elem) ||  ((*elem)->type != REDIR_IN && (*elem)->type != REDIR_OUT
		// 		&& (*elem)->type != DREDIR_OUT && (*elem)->type != HERE_DOC
		// 		&& (*elem)->type != WORD && (*elem)->type != ENV
		// 		&& (*elem)->type != START_SUBSHELL && (*elem)->type != QOUTE
		// 		&& (*elem)->type != DOUBLE_QUOTE))
			return (0);
	}
	else if ((*elem) && is_redirection((*elem)->type))
	{
		(*elem) = (*elem)->next;
		while ((*elem) && (*elem)->type == WHITE_SPACE)
			(*elem) = (*elem)->next;
		if (!(*elem) || ((*elem)->type != WORD 
                && (*elem)->type != ENV && (*elem)->type != QOUTE 
                && (*elem)->type != DOUBLE_QUOTE && (*elem)->type != WILDCARD))
			return (0);
	}
	return (1);
}

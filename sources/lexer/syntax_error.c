/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:43:39 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 08:44:37 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

static int	word_syntax(t_elem **elem)
{
	t_elem	*tmp;

	if ((*elem) && (*elem)->type == WORD)
	{
		tmp = (*elem)->next;
		while (tmp && tmp->type == WHITE_SPACE)
			tmp = tmp->next;
		if (tmp && tmp->type == START_SUBSHELL)
			return (0);
	}
	return (1);
}

static int	subshell_syntax(t_elem **elem)
{
	if (*elem && (*elem)->type == START_SUBSHELL)
	{
		*elem = (*elem)->next;
		while (elem && (*elem)->type == WHITE_SPACE)
			*elem = (*elem)->next;
		if (!*elem || (*elem)->type == END_SUBSHELL
			|| is_spliter((*elem)->type))
			return (0);
		return (1);
	}
	else if ((*elem) && (*elem)->type == END_SUBSHELL)
	{
		*elem = (*elem)->next;
		while (*elem && (*elem)->type == WHITE_SPACE)
			*elem = (*elem)->next;
		if (!*elem)
			return (1);
		if ((*elem)->type == WORD)
			return (0);
		if (*elem && (((*elem)->type != END_SUBSHELL \
			&& !is_spliter((*elem)->type) && (*elem)->type != REDIR_IN \
			&& (*elem)->type != REDIR_OUT) || (*elem)->type == START_SUBSHELL))
			return (0);
	}
	return (2);
}

static int	syntax_checker(t_elem **elem, t_list **original, t_list **list)
{
	int	a;

	if (word_syntax(elem) == 0)
		return (0);
	if ((*elem) && ((*elem)->type == START_SUBSHELL
			|| (*elem)->type == END_SUBSHELL))
	{
		a = subshell_syntax(elem);
		if (a == 0)
			return (0);
		else if (a == 1)
			return (1);
	}
	if ((*elem) && (is_redirection((*elem)->type) || is_spliter((*elem)->type)))
	{
		if (other_syntax(elem, list, original) == 0)
			return (0);
	}
	else if ((*elem))
		(*elem) = (*elem)->next;
	return (2);
}

t_list	*syntax_error(t_elem *elem)
{
	int		i;
	t_list	*list;
	t_list	*original;
	int		a;

	list = NULL;
	original = NULL;
	if (elem == NULL)
		return (NULL);
	ft_lstadd_back(&original, ft_lstnew(ft_strdup("start")));
	i = 1;
	while (elem && elem->type == WHITE_SPACE)
		elem = elem->next;
	if (elem->type == AND || elem->type == OR || elem->type == PIPE_LINE)
		return (original);
	while (elem)
	{
		a = syntax_checker(&elem, &original, &list);
		if (a == 0)
			return (original);
		else if (a == 1)
			continue ;
	}
	ft_alloc(0, list, FREE_PTR);
	return (NULL);
}

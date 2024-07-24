/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:43:39 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 11:06:34 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

void	add_limiter(t_elem **tmp, t_list **original, t_list **list)
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

int	subshell_syntax(t_elem **elem)
{
	if (*elem && (*elem)->type == START_SUBSHELL)
	{
		*elem = (*elem)->next;
		while (elem && (*elem)->type == WHITE_SPACE)
			*elem = (*elem)->next;
		if (!*elem || (*elem)->type == END_SUBSHELL || (*elem)->type == AND
			|| (*elem)->type == OR || (*elem)->type == PIPE_LINE)
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
		if (*elem && (((*elem)->type != END_SUBSHELL && (*elem)->type != AND
					&& (*elem)->type != OR && (*elem)->type != PIPE_LINE
					&& (*elem)->type != REDIR_IN && (*elem)->type != REDIR_OUT)
				|| (*elem)->type == START_SUBSHELL))
			return (0);
	}
	return (2);
}

t_list	*syntax_error(t_elem *elem)
{
	int		i;
	t_list	*list;
	t_list	*original;
			t_elem *tmp5;
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
		if (elem->type == WORD)
		{
			tmp5 = elem->next;
			while (tmp5 && tmp5->type == WHITE_SPACE)
				tmp5 = tmp5->next;
			if (tmp5 && tmp5->type == START_SUBSHELL)
				return (original);
		}
		if (elem && (elem->type == START_SUBSHELL
				|| elem->type == END_SUBSHELL))
		{
			a = subshell_syntax(&elem);
			if (a == 0)
				return (original);
			else if (a == 1)
				continue ;
		}
		if (elem && (is_redirection(elem->type) || is_spliter(elem->type)))
		{
			if (other_syntax(&elem, &list, &original) == 0)
				return (original);
		}
		else if (elem)
			elem = elem->next;
	}
	free(list);
	return (NULL);
}

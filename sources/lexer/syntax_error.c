/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:43:39 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/29 10:51:22 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

static bool is_tocken(t_elem *elem)
{
    if (elem == NULL)
        return (true);
    if (elem->type == PIPE_LINE || elem->type == REDIR_IN || elem->type == REDIR_OUT 
        || elem->type == AND || elem->type == OR || elem->type == HERE_DOC
        || elem->type == DREDIR_OUT)
        return (true);
    return (false);
}

t_list    *syntax_error(t_elem *elem)
{
    int i;
    t_elem *tmp;
    t_list *list;
    t_list *original;

    list = NULL;
    original = NULL;
    ft_lstadd_back(&original, ft_lstnew(ft_strdup("start")));
    i = 1;
    while (elem && elem->type == WHITE_SPACE)
        elem = elem->next;
    if (elem->type == AND || elem->type == OR || elem->type == PIPE_LINE)
        return (original);
    while (elem)
    {
        if (elem && elem->type == START_SUBSHELL)
        {
            elem = elem->next;
            while (elem && elem->type == WHITE_SPACE)
                elem = elem->next;
            if (!elem || elem->type == END_SUBSHELL || elem->type == AND || elem->type == OR || elem->type == PIPE_LINE)
                return (original);
            continue;
        }
        else if (elem && elem->type == END_SUBSHELL)
        {
            elem = elem->next;
            while (elem && elem->type == WHITE_SPACE)
                elem = elem->next;
            if (!elem)
                continue;
            if (elem && ((elem->type != END_SUBSHELL && elem->type != AND && elem->type != OR && elem->type != PIPE_LINE) || elem->type == START_SUBSHELL))
                return (original);
        }
        else if (elem && elem->type == HERE_DOC)
        {
            tmp = elem;
            if (tmp)
                tmp = tmp->next;
            while (tmp && tmp->type == WHITE_SPACE)
                tmp = tmp->next;
            if (tmp && !is_tocken(tmp))
            {
                if (tmp && (tmp->type == QOUTE || tmp->type == DOUBLE_QUOTE))
                {
                    tmp = tmp->next;
                    while (tmp && (tmp->type != QOUTE || tmp->type != DOUBLE_QUOTE))
                    {
                        ft_lstadd_back(&list, ft_lstnew(ft_strdup(tmp->content)));
                        tmp = tmp->next;
                    }
                    char *str;
                    str = calloc(2, 1);
                    char *tmp_str;
                    while (list)
                    {
                        tmp_str = ft_strjoin(str, list->content);
                        free(str);
                        str = tmp_str;
                        list = list->next;
                    }
                    ft_lstadd_back(&original, ft_lstnew(str));
                    elem = elem->next;
                }
                else if (tmp && tmp->type == WORD)
                {
                    ft_lstadd_back(&original, ft_lstnew(tmp->content));
                    elem = elem->next;
                }
            }
            else
                return (original);
        }
        if (elem && (elem->type == AND || elem->type == OR || elem->type == PIPE_LINE))
        {
            elem = elem->next;
            while (elem && elem->type == WHITE_SPACE)
                elem = elem->next;
            if (!elem || (elem->type != REDIR_IN && elem->type != REDIR_OUT 
                && elem->type != DREDIR_OUT && elem->type != HERE_DOC && elem->type != WORD))
                    return (original);
        }
        else if (elem && (elem->type == REDIR_IN || elem->type == REDIR_OUT 
                || elem->type == DREDIR_OUT))
        {
            elem = elem->next;
            while (elem && elem->type == WHITE_SPACE)
                elem = elem->next;
            if (!elem || (elem->type != AND && elem->type != OR && elem->type != PIPE_LINE && elem->type != WORD))
                return (original);
        }
        else if (elem)
            elem = elem->next;
    }
    free(list);
    return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:43:39 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 10:35:32 by nbenyahy         ###   ########.fr       */
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

void add_limiter(t_elem **tmp, t_list **original, t_list **list)
{
    while ((*tmp) && ((*tmp)->type != QOUTE || (*tmp)->type != DOUBLE_QUOTE))
    {
        ft_lstadd_back(list, ft_lstnew(ft_strdup((*tmp)->content)));
        (*tmp) = (*tmp)->next;
    }
    char *str;
    str = calloc(2, 1);
    char *tmp_str;
    while (list)
    {
        tmp_str = ft_strjoin(str, (*list)->content);
        free(str);
        str = tmp_str;
        *list = (*list)->next;
    }
    ft_lstadd_back(original, ft_lstnew(str));
}

t_list *here_doc_syntax(t_elem **elem, t_list **list, t_list **original)
{
    t_elem *tmp;

    tmp = *elem;
    if (tmp)
        tmp = tmp->next;
    while (tmp && tmp->type == WHITE_SPACE)
        tmp = tmp->next;
    if (tmp && !is_tocken(tmp))
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

int subshell_syntax(t_elem **elem)
{
    if (*elem && (*elem)->type == START_SUBSHELL)
    {
        *elem = (*elem)->next;
        while (elem && (*elem)->type == WHITE_SPACE)
            *elem = (*elem)->next;
        if (!*elem || (*elem)->type == END_SUBSHELL || (*elem)->type == AND || (*elem)->type == OR || (*elem)->type == PIPE_LINE)
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
        if (*elem && (((*elem)->type != END_SUBSHELL && (*elem)->type != AND && (*elem)->type != OR && (*elem)->type != PIPE_LINE && (*elem)->type != REDIR_IN && (*elem)->type != REDIR_OUT) || (*elem)->type == START_SUBSHELL))
            return (0);
    }
    return (2);
}

int other_syntax(t_elem **elem, t_list **list, t_list **original)
{
    if (*elem && (*elem)->type == HERE_DOC)
    {
            if (here_doc_syntax(elem, list, original) != NULL)
                return (0);
    }
    else if ((*elem) && ((*elem)->type == AND || (*elem)->type == OR || (*elem)->type == PIPE_LINE))
    {
        (*elem) = (*elem)->next;
        while ((*elem) && (*elem)->type == WHITE_SPACE)
            (*elem) = (*elem)->next;
        if (!(*elem) || ((*elem)->type != REDIR_IN && (*elem)->type != REDIR_OUT 
            && (*elem)->type != DREDIR_OUT && (*elem)->type != HERE_DOC && (*elem)->type != WORD && (*elem)->type != ENV && (*elem)->type != START_SUBSHELL && (*elem)->type != QOUTE && (*elem)->type != DOUBLE_QUOTE))
                return (0);
    }
    else if ((*elem) && ((*elem)->type == REDIR_IN || (*elem)->type == REDIR_OUT 
            || (*elem)->type == DREDIR_OUT))
    {
        (*elem) = (*elem)->next;
        while ((*elem) && (*elem)->type == WHITE_SPACE)
            (*elem) = (*elem)->next;
        if (!(*elem) || ((*elem)->type != WORD && (*elem)->type != ENV && (*elem)->type != QOUTE && (*elem)->type != DOUBLE_QUOTE && (*elem)->type != WILDCARD))
            return (0);
    }
    return (1);
}

t_list    *syntax_error(t_elem *elem)
{
    int i;
    t_list *list;
    t_list *original;

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
            t_elem *tmp5;
            tmp5 = elem->next;
            while (tmp5 && tmp5->type == WHITE_SPACE)
                tmp5 = tmp5->next;
            if (tmp5 && tmp5->type == START_SUBSHELL)
                return (original);
        }
        if (elem && (elem->type == START_SUBSHELL || elem->type == END_SUBSHELL))
        {
            int a = subshell_syntax(&elem);
            if (a == 0)
                return (original);
            else if (a == 1)
                continue;
        }
        // else if (elem && elem->type == HERE_DOC)
        // {
        //     if (here_doc_syntax(elem, &list, &original) != NULL)
        //         return (original);
        // }
        if (elem && ((elem->type == AND || elem->type == HERE_DOC || elem->type == OR || elem->type == PIPE_LINE) || (elem->type == REDIR_IN || elem->type == REDIR_OUT || elem->type == DREDIR_OUT)))
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

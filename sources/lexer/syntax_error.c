/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:43:39 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/19 13:52:15 by nbenyahy         ###   ########.fr       */
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

int    syntax_error(t_elem *elem)
{
    while (elem)
    {
        if (elem->type == START_SUBSHELL)
        {
            elem = elem->next;
            while (elem && elem->type == WHITE_SPACE)
                elem = elem->next;
            if (!elem || elem->type == END_SUBSHELL)
                return (258);
            continue;
        }
        if (elem->type == END_SUBSHELL)
        {
            elem = elem->next;
            while (elem && elem->type == WHITE_SPACE)
                elem = elem->next;
            if (!elem)
                continue;
            if (elem && ((elem->type != END_SUBSHELL && elem->type != AND && elem->type != OR && elem->type != PIPE_LINE) || elem->type == START_SUBSHELL))
                return (258);
        }
        if (is_tocken(elem)  == true)
        {
            elem = elem->next;
            while (elem && elem->type == WHITE_SPACE)
                elem = elem->next;
            if (is_tocken(elem) == true)
                return (258);
        }
        elem = elem->next;
    }
    return (0);
}
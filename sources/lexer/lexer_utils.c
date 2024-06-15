/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:08:36 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/15 17:09:19 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

void free_elem(t_elem *elem)
{
    t_elem *prev;

    while (elem)
    {
        prev = elem;
        elem = elem->next;
        free(prev->content);
        free(prev);
    }
}

int allocate_node(t_elem **elem, char *content, int state, int token)
{
    t_elem *new_node;
    t_elem *last_node;
    
    if (!content || content[0] == '\0')
        return (0);
    new_node = malloc(sizeof(t_elem));
    if (!new_node)
        return (1);
    new_node->state = state;
    new_node->type = token;
    new_node->content = content;
    new_node->next = NULL;
    
    if (!(*elem))
        (*elem) = new_node;
    else {
        last_node = *elem;
        while (last_node->next)
            last_node = last_node->next;
        last_node->next = new_node;
    }
    return (0);
}
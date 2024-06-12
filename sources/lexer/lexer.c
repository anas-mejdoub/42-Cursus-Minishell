/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/12 19:16:53 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

int is_token(char c)
{
    if (c != WHITE_SPACE && c != NEW_LINE && c != QOUTE && c != DOUBLE_QUOTE && c != ESCAPE
    && c != ENV && c != PIPE_LINE && c != REDIR_IN && c != REDIR_OUT)
        return (1);
    return (0);
}

int env_handeler(t_elem *elem, char *line, int i)
{
    int current_index = i;
    t_elem *new_node;

    while (is_token(line[i]))
        i++;
    new_node = malloc(sizeof(t_elem));
    new_node->content = ft_substr(line, current_index, i - current_index);
    new_node->state = GENERAL;
    new_node->type = ENV;
    new_node->next = NULL;
    if (!elem)
        elem = new_node;
    else
        elem->next = new_node;
}

t_elem *tokenize(char *line)
{
    int i = 0;
    t_elem *elem = NULL;
    elem = malloc(sizeof(t_elem));
    while (line[i])
    {
        while (line[i] == ' ')
            i++;
        if (line[i] == ENV)
            env_handeler(elem, i);
        i++;
    }
}


void lexer()
{
    t_elem *elem = NULL;
    while (1)
    {
        char* line = readline("tchbi7a-shell$");
        if (line) {
            elem = tokenize(line);
            while (elem)
            {
                printf("%s\n", elem->content);
                elem = elem->next;
            }
            free(line);
        }
    }
}

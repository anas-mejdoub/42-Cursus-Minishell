/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/14 19:32:55 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

int allocate_node(t_elem **elem, char *content, int state, int token)
{
    t_elem *new_node;
    t_elem *last_node;
    
    new_node = malloc(sizeof(t_elem));
    if (!new_node)
        return (1);
    new_node->state = state;
    new_node->type = token;
    new_node->content = content;
    // printf("content: %s\n", new_node->content);
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

int is_token(char c)
{
    if (c != WHITE_SPACE && c != NEW_LINE && c != QOUTE && c != DOUBLE_QUOTE && 
         c != ENV && c != PIPE_LINE && c != REDIR_IN && c != REDIR_OUT &&  
         c!= START_SUBSHELL && c!= END_SUBSHELL && c != WILDCARD)
        return (1);
    return (0);
}

int env_handeler(t_elem **elem, char *line, int *i, int state)
{
    int current_index = (*i);
    char *content;

    (*i)++;
    while (line[(*i)] && is_token(line[(*i)]))
        (*i)++;
    content = ft_substr(line, current_index, (*i) - current_index);
    allocate_node(elem, content, state, ENV);
    return (0);
}

void qoute_handler(t_elem **elem, char *line, int *i)
{
    int current_index;
    char *content;

    if (line[(*i)] == QOUTE)
    {
        content = ft_strdup("\'");
        allocate_node(elem,content, IN_QUOTE, QOUTE);
        (*i)++;
        current_index = (*i);
    }
    while (line[(*i)] && line[(*i)] != QOUTE)
    {
        while (line[(*i)] && line[(*i)] != QOUTE)
            (*i)++;
        content = ft_substr(line, current_index, (*i) - current_index);
        allocate_node(elem, content, IN_QUOTE, WORD);
    }
    if (line[(*i)] == QOUTE)
    {
        content = ft_strdup("\'");
        allocate_node(elem,content, IN_QUOTE, QOUTE);
        (*i)++;
    }
}

int general_tokens(char c, t_elem **elem, int *i)
{
    char *content;

    if (c == WHITE_SPACE || c == NEW_LINE || c == PIPE_LINE || c == REDIR_IN || c == REDIR_OUT ||
         c == START_SUBSHELL || c == END_SUBSHELL || c == WILDCARD)
    {
        content = ft_calloc(2, 1);
        content[0] = c;
        allocate_node(elem, content, GENERAL, (int)c);
        (*i)++;
    }
    return ((*i));
}

void general_handler(t_elem **elem, char *line, int *i)
{
    int current_index;
    char *content;

    current_index = (*i);
    while (line[(*i)] && (line[(*i)] != QOUTE && line[(*i)] != DOUBLE_QUOTE))
    {
        while (line[(*i)] && is_token(line[(*i)]))
            (*i)++;
        if (current_index != (*i))
        {   
            content = ft_substr(line , current_index, (*i) - current_index);
            allocate_node(elem, content, GENERAL, WORD);
            if (line[(*i)] == ENV)
                env_handeler(elem, line ,i, GENERAL);
            current_index = (*i);
        }
        current_index = general_tokens(line[(*i)], elem, i);
        if (line [(*i)] && (line[(*i)] == QOUTE || line[(*i)] == DOUBLE_QUOTE))
            break;
    }
}

t_elem *tokenize(char *line)
{
    int i = 0;
    t_elem *elem = NULL;
    while (line[i])
    {
        while (line[i] && line[i] == ' ')
            i++;
        if (line[i] && line[i] == QOUTE)
            qoute_handler(&elem ,line, &i);
        else if (line[i])
            general_handler(&elem, line, &i);
        // if (line[i])
        //     i++;
    }
    return (elem);
}


t_elem *lexer()
{
    t_elem *elem = NULL;
    char* line = readline("tchbi7a-shell$");
    if (line) {
        elem = tokenize(line);
        free(line);
    }
    return (elem);
}

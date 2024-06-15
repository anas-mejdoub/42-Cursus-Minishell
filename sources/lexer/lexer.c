/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/15 11:04:23 by nbenyahy         ###   ########.fr       */
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
    if (content == NULL)
        return (1);
    if (allocate_node(elem, content, state, ENV))
        return (1);
    return (0);
}

int qoute_handler(t_elem **elem, char *line, int *i)
{
    int current_index;
    char *content;

    if (line[(*i)] == QOUTE)
    {
        content = ft_strdup("\'");
        if (content == NULL)
            return (1);
        if (allocate_node(elem,content, IN_QUOTE, QOUTE))
            return (1);
        (*i)++;
        current_index = (*i);
    }
    while (line[(*i)] && line[(*i)] != QOUTE)
    {
        while (line[(*i)] && line[(*i)] != QOUTE)
            (*i)++;
        content = ft_substr(line, current_index, (*i) - current_index);
        if (content == NULL)
            return (1);
        if (allocate_node(elem, content, IN_QUOTE, WORD))
            return (1);
    }
    if (line[(*i)] == QOUTE)
    {
        content = ft_strdup("\'");
        if (content == NULL)
            return (1);
        if (allocate_node(elem,content, IN_QUOTE, QOUTE))
            return (1);
        (*i)++;
        return (0);
    }
    else
    {
        printf(RED "synthax error : messing a quote\n" RESET);
        return (1);
    }
}

int double_qoute_handler(t_elem **elem, char *line, int *i)
{
    int current_index;
    char *content;

    if (line[(*i)] == DOUBLE_QUOTE)
    {
        content = ft_strdup("\"");
        if (content == NULL)
            return (1);
        if (allocate_node(elem,content, IN_DQUOTE, DOUBLE_QUOTE))
            return (1);
        (*i)++;
        current_index = (*i);
    }
    while (line[(*i)] && line[(*i)] != DOUBLE_QUOTE)
    {
        while (line[(*i)] && line[(*i)] != DOUBLE_QUOTE)
            (*i)++;
        content = ft_substr(line, current_index, (*i) - current_index);
        if (content == NULL)
            return (1);
        if (allocate_node(elem, content, IN_DQUOTE, WORD))
            return (1);
    }
    if (line[(*i)] == DOUBLE_QUOTE)
    {
        content = ft_strdup("\"");
        if (content == NULL)
            return (1);
        if (allocate_node(elem,content, IN_DQUOTE, DOUBLE_QUOTE))
            return (1);
        (*i)++;
        return (0);
    }
    else
    {
        printf(RED "synthax error : messing a double quote\n" RESET);
        return (1);
    }
}

int general_tokens(char c, t_elem **elem, int *i)
{
    char *content;

    if (c == WHITE_SPACE || c == NEW_LINE || c == PIPE_LINE || c == REDIR_IN || c == REDIR_OUT ||
         c == START_SUBSHELL || c == END_SUBSHELL || c == WILDCARD)
    {
        content = ft_calloc(2, 1);
        if (content == NULL)
            return (1);
        content[0] = c;
        if (allocate_node(elem, content, GENERAL, (int)c))
            return (1);
        (*i)++;
    }
    return (0);
}

int general_handler(t_elem **elem, char *line, int *i)
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
            if (content == NULL)
                return (1);
            if (allocate_node(elem, content, GENERAL, WORD))
                return (1);
            if (line[(*i)] == ENV)
                if (env_handeler(elem, line ,i, GENERAL))
                    return (1);
            current_index = (*i);
        }
        if (general_tokens(line[(*i)], elem, i))
            return (1);
        current_index = (*i);
        if (line [(*i)] && (line[(*i)] == QOUTE || line[(*i)] == DOUBLE_QUOTE))
            break;
    }
    return (0);
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
        {
            if (qoute_handler(&elem ,line, &i))
                return (free(elem), NULL);
        }
        else if (line[i] && line[i] == DOUBLE_QUOTE)
        {
            if (double_qoute_handler(&elem, line, &i))
                return (free(elem), NULL);
        }
        else if (line[i])
        {
            if (general_handler(&elem, line, &i))
                return (free(elem), NULL);
        }

    }
    return (elem);
}


t_elem *lexer()
{
    t_elem *elem = NULL;
    char* line = readline(BHMAG "tchbi7a-shell$ " RESET);
    if (line) {
        elem = tokenize(line);
        free(line);
    }
    return (elem);
}

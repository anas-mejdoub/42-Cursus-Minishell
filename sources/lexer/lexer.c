/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/15 18:06:25 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

void shift_string(char *str, int shift)
{
    int len = strlen(str);
    memmove(str, str + shift, len - shift + 1); // +1 for the null terminator
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
        printf(RED "synthax error : missing a quote\n" RESET);
        return (1);
    }
}

int dquote_env(t_elem **elem, char *line, int *i, int *index)
{
    int current_index;
    char *content;
    
    (*i)++;
    current_index = (*i);
    if (ft_isdigit(line[(*i)]))
    {
        content = ft_substr(line, (*index), (*i) - 1 - (*index));
        if (content == NULL)
            return (1);
        if (allocate_node(elem, content, IN_DQUOTE, WORD))
             return (1);
        content = ft_calloc(3, 1);
        content[0] = '$';
        content[1] = line[(*i)];
        (*i)++;
        if(allocate_node(elem ,content, IN_DQUOTE, ENV))
            return (1);
        (*index) = (*i);
    } 
    else if (ft_isalpha(line[(*i)]) || line[(*i)] == '_')
    {
        content = ft_substr(line, (*index), (*i) - 1 - (*index));
        if (content == NULL)
            return (1);
        if (allocate_node(elem, content, IN_DQUOTE, WORD))
             return (1);
        while (ft_isalnum(line[(*i)]) || line[(*i)] == '_')
            (*i)++;
        if ((*i) != current_index)
        {
            content = ft_substr(line, current_index - 1, (*i) - current_index + 1);
            if (!content)
                return (1);
            if (allocate_node(elem, content, IN_DQUOTE, ENV))
                return (1);
            (*index) = (*i);
        }
    }
    else if (line[(*i)] == '*')
        memmove(line + (*i) - 1, line + (*i) + 1, strlen(line + (*i) + 1) + 1);
    return (0);
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
        {
            if (line[(*i)] == ENV)
            {
                dquote_env(elem, line, i, &current_index);
            }
            else
                (*i)++;
        }
        if ((*i) != current_index)
        {
            content = ft_substr(line, current_index, (*i) - current_index);
            if (content == NULL)
                return (1);
            if (allocate_node(elem, content, IN_DQUOTE, WORD))
                return (1);
        }
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
        printf(RED "synthax error : missing a double quote\n" RESET);
        return (1);
    }
}

int general_tokens(char c, t_elem **elem, int *i, int *subshell)
{
    char *content;

    if (c == WHITE_SPACE || c == NEW_LINE || c == PIPE_LINE || c == REDIR_IN || c == REDIR_OUT ||
         c == START_SUBSHELL || c == END_SUBSHELL || c == WILDCARD)
    {
        if (c == START_SUBSHELL)
            (*subshell)++;
        if (c == END_SUBSHELL)
            (*subshell)--;
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

int general_handler(t_elem **elem, char *line, int *i, int *subshell)
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
        if (general_tokens(line[(*i)], elem, i, subshell))
            return (1);
        current_index = (*i);
        if (line [(*i)] && (line[(*i)] == QOUTE || line[(*i)] == DOUBLE_QUOTE))
            break;
    }
    return (0);
}

t_elem *tokenize(char *line, int subshell)
{
    int i = 0;
    t_elem *elem = NULL;
    while (line[i] && line[i] == ' ')
        i++;
    while (line[i])
    {
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
            if (general_handler(&elem, line, &i, subshell))
                return (free(elem), NULL);
        }
    }
    return (elem);
}

t_elem *lexer()
{
    t_elem *elem = NULL;
    char* line = readline(BHMAG "➜ tchbi7a-shell$ " RESET);
    if (line) {
        elem = tokenize(line, subshell);
        free(line);
    }
    if (subshell != 0)
    {
        printf(RED "synthax error : missing a parenthese symbole\n" RESET);
        return(free_elem(elem), NULL);
    }
    return (elem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:12:28 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/05 09:32:06 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_lexer.h"

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
    int current_index;
    
    (*i)++;
    current_index = (*i);
    if (line[(*i)] == '?')
    {
        (*i)++;
        if (allocate_node(elem, ft_substr(line, current_index - 1, (*i) - current_index + 1), state, ENV))
                return (1);
    }
    else if (ft_isalpha(line[(*i)]) || line[(*i)] == '_')
    {
        while (line[(*i)] && (ft_isalnum(line[(*i)]) || line[(*i)] == '_'))
            (*i)++;
        if ((*i) != current_index)
        {
            if (allocate_node(elem, ft_substr(line, current_index - 1, (*i) - current_index + 1), state, ENV))
                return (1);
        }
    }
    return (0);
}

int qoute_handler(t_elem **elem, char *line, int *i)
{
    int current_index;

    if (line[(*i)] == QOUTE)
    {
        if (allocate_node(elem,ft_strdup("\'"), GENERAL, QOUTE))
            return (1);
        (*i)++;
        current_index = (*i);
    }
    while (line[(*i)] && line[(*i)] != QOUTE)
    {
        while (line[(*i)] && line[(*i)] != QOUTE)
            (*i)++;;
        if (allocate_node(elem, ft_substr(line, current_index, (*i) - current_index), IN_QUOTE, WORD))
            return (1);
    }
    if (line[(*i)] == QOUTE)
    {
        if (allocate_node(elem, ft_strdup("\'"), GENERAL, QOUTE))
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

int double_qoute_handler(t_elem **elem, char *line, int *i)
{
    int current_index;

    if (line[(*i)] == DOUBLE_QUOTE)
    {
        if (allocate_node(elem,ft_strdup("\""), GENERAL, DOUBLE_QUOTE))
            return (1);
        (*i)++;
        current_index = (*i);
    }
    while (line[(*i)] && line[(*i)] != DOUBLE_QUOTE)
    {
        while (line[(*i)] && line[(*i)] != DOUBLE_QUOTE && 
               !(line[(*i)] == ENV && (ft_isalpha(line[(*i) + 1]) || line[(*i) + 1] == '_' || line[(*i) + 1] == '?')))
            (*i)++;
        if ((*i) != current_index)
        {
            if (allocate_node(elem, ft_substr(line, current_index, (*i) - current_index), IN_DQUOTE, WORD))
                return (1);
        }
        if (line[(*i)] == ENV && (ft_isalpha(line[(*i) + 1]) || line[(*i) + 1] == '_' || line[(*i) + 1] == '?'))
        {
            if (env_handeler(elem, line ,i, IN_DQUOTE))
                return (1);
        }
        current_index = (*i);
    }
    if (line[(*i)] == DOUBLE_QUOTE)
    {
        if (allocate_node(elem, ft_strdup("\""), GENERAL, DOUBLE_QUOTE))
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

int general_tokens(char *line, t_elem **elem, int *i, int *subshell)
{
    char *content;

    content = NULL;
    if (line[(*i)] == WHITE_SPACE || line[(*i)] == NEW_LINE || line[(*i)] == PIPE_LINE || line[(*i)] == REDIR_IN || line[(*i)] == REDIR_OUT ||
         line[(*i)] == START_SUBSHELL || line[(*i)] == END_SUBSHELL || line[(*i)] == WILDCARD || line[(*i)] == '&')
    {
        if (line[(*i)] == START_SUBSHELL)
            (*subshell)++;
        if (line[(*i)] == END_SUBSHELL)
            (*subshell)--;
        if (line[(*i)] == PIPE_LINE && line[(*i) + 1] == PIPE_LINE)
        {
            allocate_node(elem, ft_strdup("||"), GENERAL, OR);
            (*i) += 2;
        }
        else if (line[(*i)] == REDIR_OUT && line[(*i) + 1] == REDIR_OUT)
        {
            allocate_node(elem, ft_strdup(">>"), GENERAL, DREDIR_OUT);
            (*i) += 2;
        }
        else if (line[(*i)] == '&' && line[(*i) + 1] == '&')
        {
            allocate_node(elem, ft_strdup("&&"), GENERAL, AND);
            (*i) += 2;
        }
        else if (line[(*i)] == '<' && line[(*i) + 1] == '<')
        {
            allocate_node(elem, ft_strdup("<<"), GENERAL, HERE_DOC);
            (*i) += 2;
        }
        else if (line[(*i)] != '&')
        {
            content = ft_calloc(2, 1);
            content[0] = line[(*i)];
            allocate_node(elem, content, GENERAL, (int)line[(*i)]);
            (*i)++;
        }
    }
    return (0);
}

int general_handler(t_elem **elem, char *line, int *i, int *subshell)
{
    int current_index;

    current_index = (*i);
    while (line[(*i)] && (line[(*i)] != QOUTE && line[(*i)] != DOUBLE_QUOTE))
    {
        while (((line[(*i)] && (is_token(line[(*i)]) && !(line[(*i)] == '&' && line[(*i) + 1] == '&')))
                || (line[(*i)] == ENV && !ft_isalpha(line[(*i) + 1]) && line[(*i) + 1] != '_' && line[(*i) + 1] != '?')))
            (*i)++;
        if (current_index != (*i))
        {   
            if (allocate_node(elem, ft_substr(line , current_index, (*i) - current_index), GENERAL, WORD))
                return (1);
            current_index = (*i);
        }
        if (line[(*i)] == ENV && (ft_isalpha(line[(*i) + 1]) || line[(*i) + 1] == '_' || line[(*i) + 1] == '?'))
        {
            if (env_handeler(elem, line ,i, GENERAL))
                return (1);
        }
        else if (general_tokens(line, elem, i, subshell))
            return (1);
        current_index = (*i);
    }
    return (0);
}

t_elem *tokenize(char *line, int *subshell)
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


void handle_sigint(int sig) 
{
    (void)sig;
    printf(BHMAG "\n" RESET);
    rl_on_new_line(); 
    // rl_replace_line("", 0);
    rl_redisplay();
}


t_elem *lexer()
{
    int subshell;

    subshell = 0;
    t_elem *elem = NULL;
    signal(SIGINT, handle_sigint);
    char* line = readline(BHMAG "➜ tchbi7a-shell$ " RESET);
    if (line == NULL) {
        exit(0);
    }
    if (line && *line) {
        add_history(line);
        elem = tokenize(line, &subshell);
        free(line);
    }
    if (subshell != 0)
    {
        printf(RED "syntax error : missing a parenthese symbole\n" RESET);
        return(free_elem(elem), NULL);
    }
    t_list *list = syntax_error(elem);
    if (list)
    {
        printf(RED "syntax error : unexpected token\n" RESET);
        list = list->next;
        while (list)
        {
            char *str = here_doc(list->content);
            free(str);
            list = list->next;
        }
        return(free_elem(elem), NULL);
    }
    return (elem);
}

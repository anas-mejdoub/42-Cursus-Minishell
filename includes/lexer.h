/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:53:40 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/12 17:15:29 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H
#include "minishell.h"
// #include "../slocal_lexer.h"
enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	START_SUBSHELL = '(',
	END_SUBSHELL = ')',
	WILDCARD = '*',
	AND,
	OR,
	HERE_DOC,
	DREDIR_OUT,
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

typedef struct s_elem
{
	char            *content;
	int             len;
	enum e_token	type;
	enum e_state	state;
	void			*next;
}	t_elem;

t_elem *lexer(void);
void handle_sigint(int sig);
// int allocate_node(t_elem **elem, char *content, int state, int token);
#endif

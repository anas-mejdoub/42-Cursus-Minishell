/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_lexer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:06:17 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/23 13:15:54 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_LEXER_H
# define LOCAL_LEXER_H

#include "minishell.h"
#include "lexer.h"

void free_elem(t_elem *elem);
int allocate_node(t_elem **elem, char *content, int state, int token);
t_list    *syntax_error(t_elem *elem);
int	general_tokens(char *line, t_elem **elem, int *i, int *subshell);
#endif
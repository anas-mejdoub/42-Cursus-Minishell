/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_lexer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:06:17 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/27 12:10:27 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_LEXER_H
# define LOCAL_LEXER_H

# include "minishell.h"
# include "lexer.h"

// void	free_elem(t_elem *elem);
void free_content(void *ptr);
int		allocate_node(t_elem **elem, char *content, int state, int token);
int		env_handeler(t_elem **elem, char *line, int *i, int state);
t_list	*syntax_error(t_elem *elem);
int		double_qoute_handler(t_elem **elem, char *line, int *i);
int		qoute_handler(t_elem **elem, char *line, int *i);
int		general_handler(t_elem **elem, char *line, int *i, int *subshell);
t_elem	*tokenize(char *line, int *subshell, t_elem **elem);
t_elem	*check_syntax_error(t_list *list);
int		other_syntax(t_elem **elem, t_list **list, t_list **original);

#endif
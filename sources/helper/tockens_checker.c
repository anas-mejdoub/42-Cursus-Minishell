/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockens_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:52:42 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/26 10:00:07 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

bool	is_redirection(char c)
{
	return (c == DREDIR_OUT || c == HERE_DOC || c == REDIR_OUT
		|| c == REDIR_IN);
}

bool	is_spliter(char c)
{
	return (c == AND || c == OR || c == PIPE_LINE);
}
bool	is_red_spliter(char c)
{
	return (is_spliter(c) || is_redirection(c));
}
bool	is_qoutes(char c)
{
	return (c == QOUTE || c == DOUBLE_QUOTE);
}

bool	in_qoutes(char c)
{
	return (c == IN_QUOTE || c == IN_DQUOTE);
}
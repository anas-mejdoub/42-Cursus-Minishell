/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:16:24 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 14:53:01 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	intialize_parser(t_command **command, t_command **pipe_node, bool *f,
		int *r)
{
	*command = new_node();
	*pipe_node = new_node();
	(*pipe_node)->type_node = ROOT_NODE;
	(*pipe_node)->right = *command;
	*r = 0;
	*f = true;
}

int	get_rank(int n)
{
	if (n == PIPE_LINE)
		return (P);
	if (n == AND)
		return (A);
	if (n == OR)
		return (O);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:19:41 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 14:54:07 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	split_tree(t_elem **elements, t_command **command, t_command **pipe_node,
		int *r)
{
	if (get_rank((*elements)->type) >= *r)
	{
		*pipe_node = handle_pipe_node(*pipe_node, (*elements)->type);
		if (!*pipe_node)
			return (0);
		*command = new_node();
		(*pipe_node)->left = *command;
		*r = get_rank((*elements)->type);
	}
	else
	{
		*command = handle_pipe_node(*command, (*elements)->type);
		(*pipe_node)->left = handle_pipe_node((*pipe_node)->left,
				(*elements)->type);
		(*command)->left = new_node();
		*command = (*command)->left;
		((t_command *)(*pipe_node)->left)->left = *command;
	}
	return (0);
}

int	first_split_tree(t_elem *elements, t_command **command,
		t_command **pipe_node, bool *f)
{
	int	r;

	r = 0;
	if (elements->type == PIPE_LINE)
		r = P;
	if (elements->type == AND)
		r = A;
	if (elements->type == OR)
		r = O;
	*f = false;
	*command = new_node();
	(*pipe_node)->left = *command;
	(*pipe_node)->type_node = set_type_node(elements->type);
	return (r);
}

bool	f_split_tree_cond(t_elem *elements, bool ft)
{
	if (elements && (elements->type == PIPE_LINE || elements->type == AND
			|| elements->type == OR) && ft == true)
		return (true);
	return (false);
}

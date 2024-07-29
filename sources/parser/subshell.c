/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:06:15 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 16:33:31 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	handle_subshell_help(t_elem **elements, t_elem **sub_set)
{
	int	lvl;

	lvl = 0;
	while (*elements != NULL)
	{
		if ((*elements)->type == END_SUBSHELL && lvl == 0)
		{
			elements = (*elements)->next;
			break ;
		}
		if ((*elements)->type == START_SUBSHELL)
			lvl++;
		if ((*elements)->type == END_SUBSHELL)
			lvl--;
		allocate_node1(sub_set, (*elements)->content, (*elements)->state,
			(*elements)->type);
		*elements = (*elements)->next;
	}
}

bool	handle_subshell(t_command *command, t_elem **elements, t_env *env)
{
	t_command	*tmp;
	t_elem		*subshell_set;

	tmp = NULL;
	subshell_set = NULL;
	handle_subshell_help(elements, &subshell_set);
	command->type_node = SUBSHELL_NODE;
	tmp = parser(subshell_set, env);
	if (!tmp)
		return (false);
	if (tmp->type_node == ROOT_NODE)
	{
		if (((t_command *)tmp->right)->type_node != ROOT_NODE)
			tmp = tmp->right;
	}
	command->right = tmp;
	return (true);
}

bool	subshell_container(t_elem **elem, t_command **cmd, t_env *env)
{
	*elem = (*elem)->next;
	if (!handle_subshell(*cmd, elem, env))
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:04:09 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 14:51:33 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

bool	redir_out_condition(t_elem *elements, t_command *command)
{
	if (elements && ((elements->type == WORD || elements->type == WILDCARD
				|| elements->type == ENV || (elements->type == QOUTE
					&& elements->next
					&& ((t_elem *)elements->next)->type == QOUTE)
				|| (elements->type == DOUBLE_QUOTE && elements->next
					&& ((t_elem *)elements->next)->type == DOUBLE_QUOTE))
			&& (command->out_redir || command->dredir)))
	{
		return (true);
	}
	return (false);
}

bool	redir_in_condition(t_elem *elements, t_command *command)
{
	if (elements && ((elements->type == WORD || elements->type == WILDCARD
				|| elements->type == ENV || (elements->type == QOUTE
					&& elements->next
					&& ((t_elem *)elements->next)->type == QOUTE)
				|| (elements->type == DOUBLE_QUOTE && elements->next
					&& ((t_elem *)elements->next)->type == DOUBLE_QUOTE))
			&& (command->in_redir || command->here_doc)))
	{
		return (true);
	}
	return (false);
}

bool	args_parse_condit(t_elem *elements, t_command *command)
{
	if ((elements->type == WORD || elements->type == WILDCARD
			|| elements->type == ENV || elements->type == QOUTE
			|| elements->type == DOUBLE_QUOTE) && !command->in_redir
		&& !command->out_redir && !command->dredir && !command->here_doc)
	{
		return (true);
	}
	return (false);
}

bool	command_args_condition(t_elem *elements, t_command *command)
{
	if ((elements->type == WORD || elements->type == WILDCARD
			|| elements->type == ENV || elements->type == QOUTE
			|| elements->type == DOUBLE_QUOTE) && !command->in_redir
		&& !command->out_redir && !command->dredir && !command->here_doc)
		return (true);
	return (false);
}

bool	split_tree_cond(t_elem *elements, bool ft)
{
	if (elements && (elements->type == PIPE_LINE || elements->type == AND
			|| elements->type == OR) && ft == false)
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:08:49 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 14:52:35 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	set_type_node(int type_elem)
{
	if (type_elem == PIPE_LINE)
		return (PIPE_LINE_NODE);
	else if (type_elem == AND)
		return (AND_NODE);
	else if (type_elem == OR)
		return (OR_NODE);
	else if (type_elem == START_SUBSHELL)
		return (SUBSHELL_NODE);
	return (0);
}

t_command	*handle_pipe_node(t_command *command, int type_elem)
{
	t_command	*pipe_node;

	pipe_node = new_node();
	if (!pipe_node)
		return (NULL);
	pipe_node->right = command;
	pipe_node->left = NULL;
	pipe_node->type_node = set_type_node(type_elem);
	return (pipe_node);
}

void	intialize_new_node(t_command *new)
{
	new->right = NULL;
	new->fd[0] = -1;
	new->fd[1] = -1;
	new->to_close = NULL;
	new->left = NULL;
	new->path = NULL;
	new->pipe = false;
	new->and_ = false;
	new->or_ = false;
	new->builtin = false;
	new->in_redir = false;
	new->out_redir = false;
	new->dredir = false;
	new->dup = false;
	new->outfiles = NULL;
	new->type_node = NODE;
	new->args = NULL;
	new->in_files = NULL;
	new->command_arg = NULL;
	new->here_doc = false;
	new->infd = -1;
	new->outfd = -1;
}

t_command	*new_node(void)
{
	t_command	*new;

	new = ft_alloc(sizeof(t_command), NULL, MALLOC);
	if (!new)
		return (0);
	intialize_new_node(new);
	return (new);
}

int	allocate_node1(t_elem **elem, char *content, int state, int token)
{
	t_elem	*new_node;
	t_elem	*last_node;

	if (!content || content[0] == '\0')
		return (0);
	new_node = ft_alloc(sizeof(t_elem), NULL, MALLOC);
	if (!new_node)
		return (1);
	new_node->state = state;
	new_node->type = token;
	new_node->content = ft_strdup(content);
	new_node->len = ft_strlen(content);
	new_node->next = NULL;
	if (!(*elem))
		(*elem) = new_node;
	else
	{
		last_node = *elem;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}

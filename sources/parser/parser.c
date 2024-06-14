/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:53:18 by amejdoub          #+#    #+#             */
/*   Updated: 2024/06/14 19:26:25 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_node(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (0);
	new->right = NULL;
	new->type_node = NODE;
	new->left = NULL;
	new->path = NULL;
	new->pipe = false;
	new->and_ = false;
	new->or_ = false;
	new->builtin = false;
	new->infile = NULL;
	new->outfile = NULL;
	new->type_node = NODE;
}

void	free2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**add_to_args(char **args, char *to_append)
{
	int		i;
	char	**new;
	int		j;

	i = 0;
	if (args)
		while (args[i])
			;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (args[i])
	{
		new[i] = ft_strdup(args[i]);
		i++;
	}
	new[i] = ft_strdup(to_append);
	new[i + 1] = NULL;
	free2d(args);
	return (new);
}

t_command	*handle_pipe_node(t_command *command)
{
	t_command	*pipe_node;

	pipe_node = new_node;
	if (!pipe_node)
		return (NULL);
	pipe_node->type_node = PIPE_LINE_NODE;
	pipe_node->right = command;
	return (pipe_node);
}

void handle_redir_in(t_command *command, char *fileanme)
{
	
}

t_command	*parser(t_elem *elements)
{
	t_command	*command;
	t_command	*pipe_node;
    t_command *root;
	bool first_time = true;

	command = new_node();
	pipe_node = new_node();
	pipe_node->type_node = PIPE_LINE_NODE;
	pipe_node->right = command;
	while (elements)
	{
		if (elements->type == WORD)
			command->command_args = add_to_args(command->command_args,
					elements->content);
		else if (elements->type == PIPE_LINE && !first_time)
		{
			pipe_node = handle_pipe_node(pipe_node);
			if (!pipe_node)
				return (NULL);
			command = new_node();
		}
		else if (elements->type == REDIR_IN)
		{

		}
		first_time = false;
	}
}

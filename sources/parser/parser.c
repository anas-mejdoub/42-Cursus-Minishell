/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:53:18 by amejdoub          #+#    #+#             */
/*   Updated: 2024/06/16 12:56:41 by amejdoub         ###   ########.fr       */
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
	new->command_args = NULL;
	new->path = NULL;
	new->pipe = false;
	new->and_ = false;
	new->or_ = false;
	new->builtin = false;
	new->infile = NULL;
	new->outfile = NULL;
	new->in_redir = false;
	new->out_redir = false;
	new->type_node = NODE;
	return (new);
}

void print_2d(t_command *command)
{
	int i = 0;
	printf("command \t infile \t outfile\n");
	while (command->command_args && command->command_args[i])
	{
		printf ("{%s} ", command->command_args[i]);
		i++;
	}
	i = 0;
	printf (" \t");
	while (command->infile && command->infile[i])
	{
		printf("(%s) ", command->infile[i]);
		i++;
	}
	if (!command->infile)
		printf("\t \t");
	printf("\t");
	i = 0;
	while (command->outfile && command->outfile[i])
	{
		printf("[%s] ", command->outfile[i]);
		i++;
	}
	printf("\n");
	
}

void	print_tree(t_command *root, int n)
{
	if (!root)
		return ;
	if (root->type_node == PIPE_LINE_NODE)
		printf("root\n");
	else if (n == 1)
		printf("right\n");
	else if (n == 2)
		printf("left\n");
	if (root->type_node == NODE)
		print_2d(root);
	print_tree(root->right, 1);
	print_tree(root->left, 2);
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

	i = 0;
	while (args && args[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (args && args[i])
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

	pipe_node = new_node();
	if (!pipe_node)
		return (NULL);
	pipe_node->type_node = PIPE_LINE_NODE;
	pipe_node->right = command;
	return (pipe_node);
}
char *command_handling(t_elem **element)
{
	char *command = NULL;
	t_elem *tmp = NULL;
	while (*element)
	{
		if (ft_strchr(" ><|()&", (*element)->type) && (*element)->state == GENERAL)
		{
			if (ft_strchr("><|()&", (*element)->type))
				*element = tmp;
			return command;
		}
		if (((*element)->state == IN_QUOTE || (*element)->state == IN_DQUOTE) && ((*element)->type != DOUBLE_QUOTE && (*element)->type != QOUTE))
		{
			if (!command)
				command = (*element)->content;
			else
				command = ft_strjoin(command, (*element)->content);
		}
		else if ((*element)->state == GENERAL)
		{
			if (!command)
				command = (*element)->content;
			else
			{
				if ((*element)->type != WHITE_SPACE)
					command = ft_strjoin(command, (*element)->content);
			}
		}
		tmp = *element;
		*element = (*element)->next;
	}
	return (command);
}
void	handle_redir_in(t_command *command, char *filename)
{
	command->infile = add_to_args(command->infile, filename);
	command->in_redir = false;
} 

void	handle_redir_out(t_command *command, char *filename)
{
	command->outfile = add_to_args(command->outfile, filename);
	command->out_redir = false;
}

t_command	*parser(t_elem *elements)
{
	t_command	*command;
	t_command	*pipe_node;
	bool		first_time;

	first_time = true;
	command = new_node();
	pipe_node = new_node();
	pipe_node->type_node = PIPE_LINE_NODE;
	pipe_node->right = command;
	while (elements)
	{
		if ((elements->type == WORD) && !command->in_redir && !command->out_redir)
			command->command_args = add_to_args(command->command_args,
					command_handling(&elements));
		else if (elements->type == PIPE_LINE && first_time == false)
		{
			pipe_node = handle_pipe_node(pipe_node);
			if (!pipe_node)
				return (NULL);
			command = new_node();
			pipe_node->left = command;
		}
		else if (elements->type == PIPE_LINE && first_time)
		{
			first_time = false;
			command = new_node();
			pipe_node->left = command;
		}
		else if (elements->type == REDIR_IN)
			command->in_redir = true;
		else if (elements->type == REDIR_OUT)
			command->out_redir = true;
		else if (elements->type == WORD && command->in_redir)
			handle_redir_in(command,command_handling(&elements));
		else if (elements->type == WORD && command->out_redir)
			handle_redir_out(command, command_handling(&elements));
		if (elements)
			elements = elements->next;
		else
			break;
	}
	return (pipe_node);
}

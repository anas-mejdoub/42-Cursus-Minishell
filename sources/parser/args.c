/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:56:44 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 14:51:21 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	command_args_parse(t_elem **elements, t_command **command)
{
	t_command_h_ret	*comm_hand_ret;

	comm_hand_ret = command_handling(elements);
	if (comm_hand_ret->env)
		add_to_command(*command, new_arg(comm_hand_ret->command,
				comm_hand_ret->including_null, comm_hand_ret->wildcard, true));
	else
		add_to_command(*command, new_arg(comm_hand_ret->command,
				comm_hand_ret->including_null, comm_hand_ret->wildcard, false));
	add_indexs_to_args(comm_hand_ret->arr, comm_hand_ret->lens,
		get_last_arg((*command)->command_arg));
}

t_command_args	*get_last_arg(t_command_args *command)
{
	while (command && command && command->next)
	{
		command = command->next;
	}
	return (command);
}

void	add_to_command(t_command *command, t_command_args *new_arg)
{
	if (!(command->command_arg))
	{
		command->command_arg = new_arg;
	}
	else
	{
		get_last_arg(command->command_arg)->next = new_arg;
	}
}

t_command_args	*new_arg(char *content, bool including_null, bool wild_card,
		bool env)
{
	t_command_args	*new;

	new = ft_alloc(sizeof(t_command_args), NULL, MALLOC);
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->env = env;
	new->wildcard = wild_card;
	new->including_null = including_null;
	new->next = NULL;
	new->index_list = NULL;
	return (new);
}

char	**add_to_args(char **args, char *to_append)
{
	int		i;
	char	**new;

	i = 0;
	while (args && args[i])
		i++;
	new = ft_alloc((sizeof(char *) * (i + 2)), NULL, MALLOC);
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

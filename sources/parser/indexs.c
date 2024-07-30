/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:02:10 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 15:06:39 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_env_index	*new_index(int new, int len)
{
	t_env_index	*new_i;

	new_i = ft_alloc(sizeof(t_env_index), NULL, MALLOC);
	if (!new_i)
		return (NULL);
	new_i->index = new;
	new_i->len = len;
	new_i->expanded = false;
	new_i->next = NULL;
	return (new_i);
}

t_env_index	*last_index(t_env_index *list)
{
	while (list && list->next)
	{
		list = list->next;
	}
	return (list);
}

void	add_to_index(t_command_args *list, t_env_index *new)
{
	if (!list->index_list)
	{
		list->index_list = new;
	}
	else
	{
		last_index(list->index_list)->next = new;
	}
}

int	env_index(char *env_str, char *prev)
{
	int	i;

	i = 0;
	while (env_str && env_str[i])
	{
		if (env_str[i] == '$')
			break ;
		i++;
	}
	return (ft_strlen(prev) + i);
}

void	add_indexs_to_args(int *arr, int *lens, t_command_args *args)
{
	int	i;

	i = 0;
	while (arr)
	{
		if (arr[i] == -1)
			break ;
		add_to_index(args, new_index(arr[i], lens[i]));
		i++;
	}
}

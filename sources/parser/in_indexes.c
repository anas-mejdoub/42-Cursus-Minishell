/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_indexes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:11:54 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 15:06:54 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	add_to_in_index(t_in_files *list, t_env_index *new)
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

void	add_indexs_to_infiles(int *arr, int *len, t_in_files *file)
{
	int	i;

	i = 0;
	while (arr)
	{
		if (arr[i] == -1)
			break ;
		add_to_in_index(file, new_index(arr[i], len[i]));
		i++;
	}
}

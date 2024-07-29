/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_indexes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:17:39 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 14:52:47 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	add_to_out_index(t_out_files *list, t_env_index *new)
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

void	add_indexs_to_outfiles(int *arr, int *len, t_out_files *file)
{
	int	i;

	i = 0;
	while (arr)
	{
		if (arr[i] == -1)
			break ;
		add_to_out_index(file, new_index(arr[i], len[i]));
		i++;
	}
}

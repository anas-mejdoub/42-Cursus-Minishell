/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:42:34 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 14:51:16 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	*add_int(int *arr, int new)
{
	int	i;
	int	*res;
	int	j;

	i = 0;
	while (arr)
	{
		if (arr[i] == -1)
			break ;
		i++;
	}
	res = ft_alloc((sizeof(int) * (i + 2)), NULL, MALLOC);
	if (!res)
		return (NULL);
	j = 0;
	while (res && j < i)
	{
		res[j] = arr[j];
		j++;
	}
	res[j] = new;
	res[j + 1] = -1;
	return (res);
}

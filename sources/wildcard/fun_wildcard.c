/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:50:43 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 10:49:24 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_wildcard.h"

static void	spliter2(char **arr, int k, char **final_string)
{
	char	**arr2;
	int		y;

	arr2 = ft_split(arr[k], '\t');
	y = 0;
	while (arr2[y])
	{
		if (ft_strchr(arr2[y], '*'))
			*final_string = ft_strjoin(*final_string, wildcard(arr2[y], '*'));
		else
			*final_string = ft_strjoin(*final_string, arr2[y]);
		y++;
		if (arr[k])
			*final_string = ft_strjoin(*final_string, " ");
	}
}

static char	*spliter(char **arr)
{
	int		k;
	char	*final_string;

	final_string = ft_calloc(1, 1);
	k = 0;
	while (arr[k])
	{
		if (ft_strchr(arr[k], '\t'))
			spliter2(arr, k, &final_string);
		else
			final_string = ft_strjoin(final_string, wildcard(arr[k], '*'));
		k++;
		if (arr[k])
			final_string = ft_strjoin(final_string, " ");
	}
	return (final_string);
}

char	*wildcard_expander(char *s)
{
	char	**arr;

	if (ft_strchr(s, ' ') || ft_strchr(s, '\t'))
	{
		arr = ft_split(s, ' ');
		return (spliter(arr));
	}
	else
		return (wildcard(s, '*'));
	return (NULL);
}

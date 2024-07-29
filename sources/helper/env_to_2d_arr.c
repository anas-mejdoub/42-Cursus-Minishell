/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_2d_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:25:07 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 11:36:17 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

static int	size_of_env(t_envata *data)
{
	t_envata	*tmp;
	int			i;

	i = 0;
	tmp = data;
	while (tmp)
	{
		if (tmp->value)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static char	**stor_it(t_envata *data, int size)
{
	int		i;
	char	**arr;
	char	*str;

	i = 0;
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);
	while (data)
	{
		if (data->value != NULL)
		{
			str = ft_strjoin(ft_strjoin(data->key, "="), data->value);
			arr[i] = str;
			i++;
		}
		data = data->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	**env_to_2d_arr(t_env *env)
{
	t_envata	*data;
	int			size;

	size = size_of_env(env->data);
	if (size == 0)
		return (NULL);
	data = env->data;
	return (stor_it(data, size));
}

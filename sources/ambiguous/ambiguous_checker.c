/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:11:17 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 11:09:03 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_ambiguous.h"

static bool	first_condition(t_amb_data *data, int j)
{
	int	g;
	int	u;

	if (data->arr[1] == NULL)
		return (true);
	else
	{
		u = 0;
		g = *data->arr_env[j];
		while (u == g && u < data->size && data->arr[u])
		{
			u++;
			if (u < data->size)
				g = *data->arr_env[u];
		}
		if (data->arr[u] == NULL)
			return (true);
	}
	return (false);
}

static void	ambiguous_hard_coding_helper(t_amb_data *data, char *ptr, bool *err,
		int *j)
{
	ptr = ft_strtrim(data->arr[*data->arr_env[(*j)]], " ");
	if ((data->arr[1] == NULL || *data->arr_env[(*j)] == 0) && (!ptr
			|| (ptr[0] == '\0' && data->arr[*data->arr_env[(*j)]][0] == '\0')))
		(*err) = first_condition(data, (*j));
	else if (data->arr[*data->arr_env[(*j)]][0] != '\0' && ft_strchr(ptr, ' '))
		(*err) = true;
	else if (ft_strlen(data->arr[*data->arr_env[(*j)]]) != 0 \
		&& data->arr[*data->arr_env[(*j)]] \
			[ft_strlen(data->arr[*data->arr_env[(*j)]]) \
		- 1] == ' ' && (*j) + 1 < data->size && data->arr[*data->arr_env[(*j) \
		+ 1]][0] != ' ')
		(*err) = true;
	else if ((data->arr[*data->arr_env[(*j)]][0] == ' ' \
			|| (ft_strlen(data->arr[*data->arr_env[(*j)]]) != 0 \
				&& data->arr[*data->arr_env[(*j)]] \
				[ft_strlen(data->arr[*data->arr_env[(*j)]]) \
				- 1] == ' ')))
		(*err) = sec_condition(data, (*j), ptr);
}

static bool	ambiguous_hard_coding(t_amb_data *data)
{
	bool	err;
	int		j;
	char	*ptr;

	ptr = NULL;
	err = false;
	j = 0;
	while (j < data->size)
	{
		ambiguous_hard_coding_helper(data, ptr, &err, &j);
		if (err)
			break ;
		j++;
	}
	return (err);
}

bool	imbg(t_elem *tmp, t_env *env)
{
	t_amb_data	*data;
	bool		status;

	data = ft_alloc(sizeof(t_amb_data), NULL, MALLOC);
	data->arr = NULL;
	data->arr_env = NULL;
	data->index = 0;
	data->size = 0;
	fill_array_element(data, tmp, env);
	status = ambiguous_hard_coding(data);
	return (status);
}

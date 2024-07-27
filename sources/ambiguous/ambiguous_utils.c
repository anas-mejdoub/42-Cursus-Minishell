/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:05:47 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/27 14:37:18 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_ambiguous.h"


static bool	therd_sub_sec_condition(t_amb_data *data, int j)
{
	bool	p1;
	bool	p2;
	int		a;

	p1 = false;
	p2 = false;
	a = *data->arr_env[j] + 1;
	while (data->arr[a])
	{
		if (data->arr[a][0] != '\0')
			break ;
		a++;
	}
	if (!data->arr[a] || (data->arr[a] && data->arr[a][0] == '\0'))
		p1 = true;
	a = *data->arr_env[j] - 1;
	while (*data->arr_env[j] != 0 && a >= 0)
	{
		if (data->arr[a][0] != '\0')
			break ;
		a--;
	}
	if (a != 0)
		p2 = true;
	if (p2 == true && p1 == true)
		return (true);
	return (false);
}

static bool	first_sub_sec_condition(t_amb_data *data, char *ptr, int *k)
{
	(*k)--;
	if (ptr[0] == '\0')
	{
		while ((*k) >= 0 && data->arr[(*k)][0] == '\0')
			(*k)--;
		if ((*k) != 0)
			return (true);
	}
	while ((*k) >= 0)
	{
		if (data->arr[(*k)][0] != '\0')
			return (true);
		(*k)--;
	}
	return (false);
}

static bool	sub_sec_sub_sec_condition(int j, int *k, t_amb_data *data)
{
	int	o;

	o = j;
	++o;
	while (o < data->size && *data->arr_env[o] == (*k)
		&& data->arr[*data->arr_env[o]]
		&& !ft_strchr(ft_strtrim(data->arr[*data->arr_env[o]], " "), ' '))
	{
		o++;
		(*k)++;
	}
	while (data->arr[(*k)] && data->arr[(*k)][0] == '\0')
		(*k)++;
	if (data->arr[(*k)])
		return (true);
	return (false);
}


static bool	sec_sub_sec_condition(t_amb_data *data, char *ptr, int *k, int j)
{
	(*k)++;
	if (ptr[0] == '\0')
	{
		while (data->arr[(*k)] && data->arr[(*k)][0] == '\0')
			(*k)++;
		if (data->arr[(*k)] == NULL)
			return (true);
	}
	else if (data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]])
		- 1] == ' ' && ptr[0] != '\0')
	{
		if (sub_sec_sub_sec_condition(j, k, data))
			return (true);
	}
	while (data->arr[(*k)])
	{
		if (data->arr[(*k)][0] != '\0'
			&& ft_strchr(ptr, ' '))
			return (true);
		(*k)++;
	}
	return (false);
}


bool	sec_condition(t_amb_data *data, int j, char *ptr)
{
	int	k;

	k = *data->arr_env[j];
	if (ft_strchr(ft_strtrim(data->arr[*data->arr_env[j]], " "), ' '))
		return (true);
	else if (*data->arr_env[j] != 0 && (data->arr[*data->arr_env[j]][0] == ' '
		&& ptr[0] != '\0'))
	{
		if (first_sub_sec_condition(data, ptr, &k))
			return (true);
	}
	else if (data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]])
		- 1] == ' ' && ptr[0] != '\0')
	{
		if (sec_sub_sec_condition(data, ptr, &k, j))
			return (true);
	}
	if (data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]])
		- 1] == ' ' && ptr[0] == '\0')
	{
		if (therd_sub_sec_condition(data, j))
			return (true);
	}
	return (false);
}

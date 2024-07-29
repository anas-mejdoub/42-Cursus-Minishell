/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:11:17 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 07:57:23 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_ambiguous.h"

int	int_append_to_array(int ***arr, int num, int size)
{
	int	**new_arr;
	int	*nbr;
	int	i;
	int	*n;

	i = 0;
	new_arr = (int **)ft_alloc(((size + 1) * sizeof(int *)), NULL, MALLOC);
	if (new_arr == NULL)
		return (-1);
	while (i < size)
	{
		n = ft_alloc(sizeof(int), NULL, MALLOC);
		*n = *(*arr)[i];
		new_arr[i] = n;
		i++;
	}
	nbr = ft_alloc(sizeof(int), NULL, MALLOC);
	*nbr = num;
	new_arr[i] = nbr;
	*arr = new_arr;
	return (size + 1);
}

static void	qoute_ambiguous_checker(t_amb_data *data, t_elem **tmp)
{
	char	*a;

	if ((*tmp) && ((*tmp)->type == QOUTE || (*tmp)->type == DOUBLE_QUOTE))
	{
		// a = ft_calloc(1, 1);
		a = ft_alloc(1, NULL, CALLOC);
		(*tmp) = (*tmp)->next;
		while (*tmp && (*tmp)->type != QOUTE && (*tmp)->type != DOUBLE_QUOTE)
		{
			a = ft_freed_join(a, (*tmp)->content);
			(*tmp) = (*tmp)->next;
		}
		data->arr = add_to_args(data->arr, a);
		data->index++;
		(*tmp) = (*tmp)->next;
	}
	else if ((*tmp) && ((*tmp)->state == IN_DQUOTE
			|| (*tmp)->state == IN_QUOTE))
	{
		data->arr = add_to_args(data->arr, (*tmp)->content);
		data->index++;
		(*tmp) = (*tmp)->next;
		(*tmp) = (*tmp)->next;
	}
}

static void	fill_array_element(t_amb_data *data, t_elem *tmp, t_env *env)
{
	char	*nv;

	while (tmp)
	{
		if (tmp && tmp->type == WORD && tmp->state == GENERAL)
		{
			data->arr = add_to_args(data->arr, tmp->content);
			data->index++;
			tmp = tmp->next;
		}
		else if (tmp && (in_qoutes(tmp->type) || is_qoutes(tmp->type)))
			qoute_ambiguous_checker(data, &tmp);
		else if (tmp && tmp->type == ENV && tmp->state == GENERAL)
		{
			nv = env->get(env->data, (tmp->content + 1));
			if (nv == NULL)
			{
				nv = ft_alloc(1, NULL, CALLOC);
				data->arr = add_to_args(data->arr, nv);
			}
			else
				data->arr = add_to_args(data->arr, nv);
			data->size = int_append_to_array(&data->arr_env, data->index,
					data->size);
			data->index++;
			tmp = tmp->next;
		}
		else
			break ;
	}
}

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

static bool	ambiguous_hard_coding(t_amb_data *data)
{
	bool	err;
	int		j;
	char	*ptr;

	err = false;
	j = 0;
	while (j < data->size)
	{
		ptr = ft_strtrim(data->arr[*data->arr_env[j]], " ");
		if ((data->arr[1] == NULL || *data->arr_env[j] == 0) && (!ptr
				|| (ptr[0] == '\0' && data->arr[*data->arr_env[j]][0] == '\0')))
			err = first_condition(data, j);
		else if (data->arr[*data->arr_env[j]][0] != '\0' && ft_strchr(ptr, ' '))
			err = true;
		else if (ft_strlen(data->arr[*data->arr_env[j]]) != 0
			&& data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]])
			- 1] == ' ' && j + 1 < data->size && data->arr[*data->arr_env[j
			+ 1]][0] != ' ')
			err = true;
		else if ((data->arr[*data->arr_env[j]][0] == ' '
				|| (ft_strlen(data->arr[*data->arr_env[j]]) != 0
					&& data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]])
					- 1] == ' ')))
			err = sec_condition(data, j, ptr);
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

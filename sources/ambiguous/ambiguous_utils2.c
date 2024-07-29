/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:55:09 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 11:01:14 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_ambiguous.h"

static int	int_append_to_array(int ***arr, int num, int size)
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

static void	helper(t_amb_data *data, t_elem **tmp, t_env *env, char *nv)
{
	nv = env->get(env->data, ((*tmp)->content + 1));
	if (nv == NULL)
	{
		nv = ft_alloc(1, NULL, CALLOC);
		data->arr = add_to_args(data->arr, nv);
	}
	else
		data->arr = add_to_args(data->arr, nv);
	data->size = int_append_to_array(&data->arr_env, data->index, data->size);
	data->index++;
	(*tmp) = (*tmp)->next;
}

void	fill_array_element(t_amb_data *data, t_elem *tmp, t_env *env)
{
	char	*nv;

	nv = NULL;
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
			helper(data, &tmp, env, nv);
		else
			break ;
	}
}

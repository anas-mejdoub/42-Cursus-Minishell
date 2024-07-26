/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:11:17 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/26 08:48:11 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_ambiguous.h"

int int_append_to_array(int ***arr, int num, int size)
{
	int **new_arr;
	int *nbr;
	int i = 0;

	new_arr = (int **)malloc((size + 1) * sizeof(int *));
	if (new_arr == NULL)
		return -1;

	while (i < size)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	nbr = malloc(sizeof(int));
	*nbr = num;
	new_arr[i] = nbr;
	*arr = new_arr;
	return (size + 1);
}

static void qoute_ambiguous_checker(t_amb_data *data, t_elem **tmp, t_env *env)
{
	if ((*tmp) && ((*tmp)->type == QOUTE || (*tmp)->type == DOUBLE_QUOTE))
	{
		char *a = ft_calloc(1, 1);
		(*tmp) = (*tmp)->next;
		while (*tmp && (*tmp)->type != QOUTE && (*tmp)->type != DOUBLE_QUOTE)
		{
			a = ft_strjoin(a, (*tmp)->content);
			(*tmp) = (*tmp)->next;
		}
		data->arr = add_to_args(data->arr, a);
		data->index++;
		(*tmp) = (*tmp)->next;
	}
	else if ((*tmp) && (*tmp)->type == ENV && (*tmp)->state == GENERAL)
	{
		char *nv = env->get(env->data, ((*tmp)->content + 1));
		if (nv == NULL)
			nv = ft_calloc(1, 1);
		data->arr = add_to_args(data->arr, nv);
		data->size = int_append_to_array(&data->arr_env, data->index, data->size);
		data->index++;
		(*tmp) = (*tmp)->next;
	}
}

static void fill_array_element(t_amb_data *data, t_elem *tmp, t_env *env)
{
	while (tmp)
	{
		if (tmp && tmp->type == WORD && tmp->state == GENERAL)
		{
			data->arr = add_to_args(data->arr, tmp->content);
			data->index++;
			tmp = tmp->next;
		}
		else if (tmp && ((tmp->state == IN_DQUOTE || tmp->state == IN_QUOTE) || (tmp->type == QOUTE || tmp->type == DOUBLE_QUOTE)))
			qoute_ambiguous_checker(data, &tmp, env);
		else if (tmp && tmp->type == ENV && tmp->state == GENERAL)
		{
			char *nv = env->get(env->data, (tmp->content + 1));
			if (nv == NULL)
				nv = ft_calloc(1, 1);
			data->arr = add_to_args(data->arr, nv);
			data->size = int_append_to_array(&data->arr_env, data->index, data->size);
			data->index++;
			tmp = tmp->next;
		}
		else
			break;
	}
}

static bool first_condition(t_amb_data *data, int j)
{
	int g;
	int u;

	if (data->arr[1] == NULL)
		return true;
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
			return true;
	}
	return false;
}

static bool sec_condition(t_amb_data *data, int j, char *ptr)
{
	int k = *data->arr_env[j];
	if (ft_strchr(ft_strtrim(data->arr[*data->arr_env[j]], " "), ' '))
		return (true);
	else if (*data->arr_env[j] != 0 && (data->arr[*data->arr_env[j]][0] == ' ' && ptr[0] != '\0'))
	{
		k--;
		if (ptr[0] == '\0')
		{
			while (k >= 0 && data->arr[k][0] == '\0')
				k--;
			if (k != 0)
				return (true);
		}
		while (k >= 0)
		{
			if (data->arr[k][0] != '\0')
				return (true);
			k--;
		}
	}
	else if (data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]]) - 1] == ' ' && ptr[0] != '\0')
	{
		k++;
		if (ptr[0] == '\0')
		{
			while (data->arr[k] && data->arr[k][0] == '\0')
				k++;
			if (data->arr[k] == NULL)
				return (true);
		}
		else if (data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]]) - 1] == ' ' && ptr[0] != '\0')
		{
			int o = j;
			++o;
			while (o < data->size && *data->arr_env[o] == k && data->arr[*data->arr_env[o]] && !ft_strchr(ft_strtrim(data->arr[*data->arr_env[o]], " "), ' '))
			{
				o++;
				k++;
			}
			while (data->arr[k] && data->arr[k][0] == '\0')
				k++;
			if (data->arr[k])
				return (true);
		}
		while (data->arr[k])
		{
			if (data->arr[k][0] != '\0' && ft_strchr(ft_strtrim(data->arr[*data->arr_env[j]], " "), ' '))
			{
				return (true);
				break;
			}
			k++;
		}
	}
	if (data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]]) - 1] == ' ' && ptr[0] == '\0')
	{
		bool p1 = false;
		bool p2 = false;
		int a = *data->arr_env[j];
		a++;
		while (data->arr[a])
		{
			if (data->arr[a][0] != '\0')
				break;
			a++;
		}
		if (!data->arr[a] || (data->arr[a] && data->arr[a][0] == '\0'))
			p1 = true;
		a = *data->arr_env[j];
		a--;
		while (*data->arr_env[j] != 0 && a >= 0)
		{
			if (data->arr[a][0] != '\0')
				break;
			a--;
		}
		if (a != 0)
			p2 = true;
		if (p2 == true && p1 == true)
			return (true);
	}
	return (false);
}


static bool ambiguous_hard_coding(t_amb_data *data)
{
	bool err;
	int j;

	err = false;
	j = 0;
	while (j < data->size)
	{
		char *ptr = ft_strtrim(data->arr[*data->arr_env[j]], " ");
		if ((data->arr[1] == NULL || *data->arr_env[j] == 0) && (!ptr || (ptr[0] == '\0' && data->arr[*data->arr_env[j]][0] == '\0')))
			err = first_condition(data, j);
		// {
		// 	if (data->arr[1] == NULL)
		// 		err = true;
		// 	else
		// 	{
		// 		int u = 0;
		// 		int g = *data->arr_env[j];
		// 		while (u == g && u < data->size && data->arr[u])
		// 		{
		// 			u++;
		// 			if (u < data->size)
		// 				g = *data->arr_env[u];
		// 		}
		// 		if (data->arr[u] == NULL)
		// 			err = true;
		// 	}
		// }
		else if (data->arr[*data->arr_env[j]][0] != '\0' && ft_strchr(ft_strtrim(data->arr[*data->arr_env[j]], " "), ' '))
			err = true;
		else if (ft_strlen(data->arr[*data->arr_env[j]]) != 0 && data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]]) - 1] == ' ' && j + 1 < data->size && data->arr[*data->arr_env[j + 1]][0] != ' ')
			err = true;
		else if ((data->arr[*data->arr_env[j]][0] == ' ' || (ft_strlen(data->arr[*data->arr_env[j]]) != 0 && data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]]) - 1] == ' ')))
			err = sec_condition(data, j, ptr);
			// {
			// 	int k = *data->arr_env[j];
			// 	if (ft_strchr(ft_strtrim(data->arr[*data->arr_env[j]], " ") ,' '))
			// 	{
			// 		err = true;
			// 		break;
			// 	}
			// 	else if (*data->arr_env[j] != 0 && (data->arr[*data->arr_env[j]][0] == ' ' && ptr[0] != '\0'))
			// 	{
			// 		k--;
			// 		if (ptr[0] == '\0')
			// 		{
			// 			while (k >= 0 && data->arr[k][0] == '\0')
			// 				k--;
			// 			if (k != 0)
			// 			{
			// 				err = true;
			// 			}
			// 		}
			// 		while (k >= 0)
			// 		{
			// 			if (data->arr[k][0] != '\0')
			// 			{
			// 				err = true;
			// 				break;
			// 			}
			// 			k--;
			// 		}
			// 	}
			// 	else if (data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]]) - 1] == ' ' && ptr[0] != '\0')
			// 	{
			// 		k++;
			// 		if (ptr[0] == '\0')
			// 		{
			// 			while (data->arr[k] && data->arr[k][0] == '\0')
			// 				k++;
			// 			if (data->arr[k] == NULL)
			// 				err = true;
			// 		}
			// 		else if (data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]]) - 1] == ' ' && ptr[0] != '\0')
			// 		{
			// 			int o = j;
			// 			++o;
			// 			while (o < data->size && *data->arr_env[o] == k && data->arr[*data->arr_env[o]] && !ft_strchr(ft_strtrim(data->arr[*data->arr_env[o]], " "), ' '))
			// 			{
			// 				o++;
			// 				k++;
			// 			}
			// 			while (data->arr[k] && data->arr[k][0] == '\0')
			// 				k++;
			// 			if (data->arr[k])
			// 				err = true;
			// 		}
			// 		while (data->arr[k])
			// 		{
			// 			if (data->arr[k][0] != '\0' && ft_strchr(ft_strtrim(data->arr[*data->arr_env[j]], " ") ,' '))
			// 			{
			// 				err = true;
			// 				break;
			// 			}
			// 			k++;
			// 		}
			// 	}
			// 	if (data->arr[*data->arr_env[j]][ft_strlen(data->arr[*data->arr_env[j]]) - 1] == ' ' && ptr[0] == '\0')
			// 	{
			// 		bool p1 = false;
			// 		bool p2 = false;
			// 		int a = *data->arr_env[j];
			// 		a++;
			// 		while (data->arr[a])
			// 		{
			// 			if (data->arr[a][0] != '\0')
			// 				break;
			// 			a++;
			// 		}
			// 		if (!data->arr[a] || (data->arr[a] && data->arr[a][0] == '\0'))
			// 			p1 = true;
			// 		a = *data->arr_env[j];
			// 		a--;
			// 		while (*data->arr_env[j] != 0 && a >= 0)
			// 		{
			// 			if (data->arr[a][0] != '\0')
			// 				break;
			// 			a--;
			// 		}
			// 		if (a != 0)
			// 			p2 = true;
			// 		if (p2 == true && p1 == true)
			// 			err = true;
			// 	}
			// }
			if (err)
				break;
		j++;
	}
	return (err);
}

bool imbg(t_elem *tmp, t_env *env)
{
	t_amb_data *data;

	data = malloc(sizeof(t_amb_data));
	data->arr = NULL;
	data->arr_env = ft_calloc(1, 4);
	data->index = 0;
	data->size = 0;
	fill_array_element(data, tmp, env);
	return (ambiguous_hard_coding(data));
}
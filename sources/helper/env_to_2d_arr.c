/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_2d_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:25:07 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/08 09:42:17 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

int size_of_env(t_env_data *data)
{
    t_env_data *tmp;
    int i;

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

char **env_to_2d_arr(t_env *env)
{
    t_env_data *data;
    char *str;
    char  **arr;
    int size;
    int i;

    // printf("hehe\n");
    size = size_of_env(env->data);
    if (size == 0)
        return (NULL);
    arr = malloc(sizeof(char  *) * (size + 1));
    if (!arr)
        return (NULL);
    data = env->data;
    i = 0;
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
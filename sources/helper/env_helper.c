/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:35:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/05 16:37:53 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

char *add_string_back(char **s1, char **s2)
{
    char *tmp;

    if ((*s2) == NULL)
        return ((*s1));
    tmp = ft_strjoin(*s1, *s2);
    *s1 = tmp;
    return (*s1);
}

char  *env_expander(char *content, t_env_index *indexs, t_env *env)
{
    int i;
    int start;
    char *tmp_str;
    char *str;
    (void) env;
    t_env_index *tmp_index;

    i = 0;
    start = i;
    tmp_index = indexs;
    if (!indexs)
        return (content);
    str = ft_calloc(1, 1);
    while (content[i])
    {
        while ((!tmp_index && content[i]) || (content[i] && tmp_index && i != tmp_index->index))
            i++;
        if (i != start)
        {
            tmp_str = ft_substr(content, start , i - start);
            str = add_string_back(&str, &tmp_str);
            start = i;
        }
        if (tmp_index && i == tmp_index->index)
        {
            i++;
            tmp_str = ft_substr(content, start + 1 , tmp_index->len - 1);
            char *s = env->get(env->data, tmp_str);
            add_string_back(&str, &s);
            start = i + tmp_index->len - 1;
            tmp_index = tmp_index->next;
        }
    }
    return (str);
}


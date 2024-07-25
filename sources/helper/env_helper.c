/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:35:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 09:55:13 by nbenyahy         ###   ########.fr       */
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

char  *env_expander(char *content, t_env_index *indexs, t_env *env, bool wild_card)
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
    if (wild_card)
    {   
        char *new_content = wildcard(content, -17);
        content = new_content;
    }
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
            if (s && ft_strchr(s, '*'))
                s = wildcard_expander(s);
            // {
                // char *final_string = ft_calloc(1,1);
                // if (ft_strchr(s, ' ') || ft_strchr(s, '\t'))
                // {
                //     char **arr = ft_split(s, ' ');
                //     int k = 0;
                //     while (arr[k])
                //     {
                //         if (ft_strchr(arr[k], '\t'))
                //         {
                //             char **arr2 = ft_split(arr[k], '\n');
                //             int y = 0;
                //             while (arr2[y])
                //             {
                //                 if (ft_strchr(arr2[y], '*'))
                //                     final_string = ft_strjoin(final_string, wildcard(arr2[y], '*'));
                //                 else
                //                     final_string = ft_strjoin(final_string, arr2[y]);
                //                 y++;
                //                 if (arr[k])
                //                     final_string = ft_strjoin(final_string, " ");
                //             }
                //         }
                //         else if (ft_strchr(arr[k], '*'))
                //             final_string = ft_strjoin(final_string, wildcard(arr[k], '*'));
                //         else
                //             final_string = ft_strjoin(final_string, wildcard(arr[k], '*'));
                //         k++;
                //         if (arr[k])
                //             final_string = ft_strjoin(final_string, " ");
                //     }
                //     s = final_string;
                // }
                // else
                //     s = wildcard(s, '*');
            // }
            add_string_back(&str, &s);
            start = i + tmp_index->len - 1;
            tmp_index = tmp_index->next;
        }
    }
    return (str);
}


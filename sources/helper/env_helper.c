/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:35:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/30 15:49:50 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

char *add_string_back(char *s1, char *s2)
{
    char *tmp;

    tmp = ft_strjoin(s1, s2);
    free(s2);
    free(s1);
    s1 = tmp;
    return (s1);
}


char  *env_handeler_test(char *line, t_env *env)
{
    int current_index;
    char *tmp;
    char *str;
    int i;
    (void)env;

    printf("hello\n");
    i = 0;
    str = ft_calloc(1, 1);
    current_index = i;
    while (line && line[i])
    {
        while (line[i] && (line[i] == ENV && !ft_isalpha(line[i + 1]) && line[i + 1] != '_' && line[i + 1] != '?'))
            i++;
        printf("hy\n");
        if (i != current_index)
        {
            tmp = ft_substr(line, current_index - 1, i - current_index + 1);
            printf("%s\n", tmp);
            // str = add_string_back(str ,tmp);
        }
        if (line[i] && line[i] == ENV)
        {
            i = current_index;
            if (line[i] && line[i] == '?')
            {
                i++;
                tmp = ft_substr(line, current_index - 1, i - current_index + 1);
                // str = add_string_back(str ,tmp);
                printf("%s\n", tmp);
                i = current_index;
            }
            else if (line[i] && (ft_isalpha(line[i]) || line[i] == '_'))
            {
                while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
                    i++;
                if (i != current_index)
                {
                    tmp = ft_substr(line, current_index - 1, i - current_index + 1);
                    printf("%s\n", tmp);
                    // str = add_string_back(str ,tmp);
                    i = current_index;
                }
            }
        }
    }
    return (NULL);
}

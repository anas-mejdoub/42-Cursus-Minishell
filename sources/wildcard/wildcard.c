/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:16:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/20 15:38:34 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_wildcard.h"

static char **dir_content(void)
{
    DIR *dir;
    struct dirent *entry;
    char **arr = NULL;

    char cwd[1024];  

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {  
        perror("getcwd");
        return (NULL);
    }
    dir = opendir(cwd); 
    if (dir == NULL)
    {
        perror("opendir");
        return (NULL);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
            arr = add_to_args(arr, entry->d_name);
    }

    closedir(dir);
    return(arr);
}

static bool matching_pattern(char* s1,  char* s2) {
    if (*s2 == '\0')
        return *s1 == '\0';
    if (*s2 == '*')
        return matching_pattern(s1, s2 + 1) || (*s1 && matching_pattern(s1 + 1, s2));
    if (*s1 == *s2)
        return matching_pattern(s1 + 1, s2 + 1);
    return false;
}

char *wildcard(char *pattern)
{
    char **content;
    char **arr_final = NULL;
    char *final_content;

    content = dir_content();
    int i = 0;

    while (content[i])
    {
        if (matching_pattern(content[i], pattern))
            arr_final = add_to_args(arr_final, content[i]);
        i++;
    }
    if (arr_final == NULL)
        return (pattern);
    else
    {
        final_content = ft_calloc(1,1);
        i = 0;
        while (arr_final[i])
        {
            final_content = ft_strjoin(final_content, arr_final[i]);
            i++;
            if (arr_final[i])
            {
                final_content = ft_strjoin(final_content, " ");
            }
        }
    }
    return (final_content);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:16:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 08:02:05 by amejdoub         ###   ########.fr       */
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

static bool matching_pattern(char* s1,  char* s2, char reg) {
    if (*s2 == '\0')
        return *s1 == '\0';
    if (*s2 == reg)
        return matching_pattern(s1, s2 + 1, reg) || (*s1 && matching_pattern(s1 + 1, s2, reg));
    if (*s1 == *s2)
        return matching_pattern(s1 + 1, s2 + 1, reg);
    return false;
}

char *wildcard(char *pattern, char reg)
{
    char **content;
    char **arr_final = NULL;
    char *final_content;

    content = dir_content();
    int i = 0;

    while (content[i])
    {
        // printf("%s\n",content[i]);
        if (matching_pattern(content[i], pattern, reg) == true)
        {
            // printf("%s\n",content[i]);
            arr_final = add_to_args(arr_final, content[i]);
        }
        i++;
    }
    if (arr_final == NULL)
    {
        // printf("bchon ymak\n");
        char *new_ptr;
        new_ptr = malloc(ft_strlen(pattern) + 1);
        int  j = 0;
        while (pattern[j])
        {
            if (pattern[j] == -17)
            {
                new_ptr[j] = '*';
            }
            else
                new_ptr[j] = pattern[j];
            j++;
        }
        new_ptr[j] = '\0';

        return (new_ptr);
    }
    else
    {
        // printf("mchi t7awa\n");
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
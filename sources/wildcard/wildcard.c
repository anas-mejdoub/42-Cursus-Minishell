/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:16:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/20 11:33:20 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_wildcard.h"

char **dir_content()
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
    if (dir == NULL) {
        perror("opendir");
        return (NULL);
    }

    printf("Contents of directory '%s':\n", cwd);

    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

}

bool MatchingPattern(char* s1,  char* s2) {
    if (*s2 == '\0') 
        return *s1 == '\0';
    if (*s2 == '*')
        return MatchingPattern(s1, s2 + 1) || (*s1 && MatchingPattern(s1 + 1, s2));
    if (*s1 == *s2)
        return MatchingPattern(s1 + 1, s2 + 1);
    return false;
}
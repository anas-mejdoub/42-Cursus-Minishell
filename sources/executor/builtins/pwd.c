/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:46:05 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/30 18:04:37 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int pwd(void)
{
    char *current_dir;
    int size;


    size = 1024;
    while (1)
    {
        current_dir = malloc(size);
        if (!current_dir)
            return (1);
        if (getcwd(current_dir, size) == NULL)
        {
            if (errno == ERANGE)
            {
                free(current_dir);
                size += size;
                continue;
            }
        }
        else
        {
            printf("%s\n", current_dir);
            free(current_dir);
            break;
        }
    }
    return (0);
}

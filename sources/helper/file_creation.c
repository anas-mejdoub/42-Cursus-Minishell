/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:48:34 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/04 18:16:56 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

int open_out_files(t_out_files *files, t_env *env)
{
    // int last_fd;
    // int i;
    char *file_name;
    (void)env;

    while (files)
    {
        if (!files->index_list)
            file_name = files->filename;
        else
            file_name = env_expander(files->filename, files->index_list, env);
        if (files->index_list && !files->in_qoute && ft_strchr(file_name, ' '))
            printf("error");
        else
            printf("%s\n", file_name);
        files = files->next;
        // if (!index)
        // {
        //     if (access(files->filename, F_OK))
        //     {
        //         if (access(files, W_OK))
        //         {
        //             last_fd  = open(files->filename, O_WRONLY);
        //             if (last_fd == -1)
        //                 return (-1);
        //             close(last_fd);
        //         }
        //     else
        //     {
        //         perror("bash: ");
        //         return (-1);
        //     }
        //     }
        // else
        // {
        //     last_fd = open(files->filename, O_WRONLY | O_CREAT, 0644);
        //     if (last_fd == -1)
        //         return (-1);
        //     clode(last_fd);
        // }
        // }
    }
    return (0);
}



// int open_out_files(char **files)
// {
//     int last_fd;
//     int i;

//     i = 0;
//     while (files[i + 1])
//     {
        
//         if (access(files[i], F_OK))
//         {
//             if (access(files[i], W_OK))
//             {
//                 last_fd  = open(files[i], O_WRONLY);
//                 if (last_fd == -1)
//                     return (-1);
//                 close(last_fd);
//             }
//             else
//             {
//                 perror("bash: ");
//                 return (-1);
//             }
//         }
//         else
//         {
//             last_fd = open(files[i], O_WRONLY | O_CREAT, 0644);
//             if (last_fd == -1)
//                 return (-1);
//             clode(last_fd);
//         }
            
//     }
// }

// int open_in_files(char **files)
// {
    
// }
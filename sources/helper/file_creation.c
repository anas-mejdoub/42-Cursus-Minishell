/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:48:34 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/05 20:38:07 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

char  *ambiguous(void *files, bool type ,t_env *env)
{
    char *file_name;
    t_out_files *file1;
    t_in_files *file2;
    
    file1 = NULL;
    file2 = NULL;
    if (type == true)
    { 
        file1 = (t_out_files *)files;
        if (!file1->index_list)
            file_name = file1->filename;
        else
            file_name = env_expander(file1->filename, file1->index_list, env);
        if (file1->index_list && !file1->in_qoute && (ft_strchr(file_name, ' ') || file_name[0] == '\0'))
            return (printf("minishell: %s: ambiguous redirect\n", file1->filename), NULL);
        else
            return (file_name);
    }
    else
    {
        file2 = (t_in_files *)files;
        if (!file2->index_list)
            file_name = file2->filename;
        else
            file_name = env_expander(file2->filename, file2->index_list, env);
        if (file2->index_list && !file2->in_qoute && (ft_strchr(file_name, ' ') || file_name[0] == '\0'))
            return (printf("minishell: %s: ambiguous redirect\n", file2->filename), NULL);
        else
            return (file_name);
    }
}

int open_file(char *file_name, bool append, bool create, bool type)
{
    if (type == true)
    {
        if (!create && !append)
            return (open(file_name, O_WRONLY | O_TRUNC));
        else if (create && append)
            return (open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666));
        else if (!create && append)
            return (open(file_name, O_WRONLY | O_APPEND));
        else if (create && !append)
            return (open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666));
    }
    else if (type == false)
        return (open(file_name, O_RDONLY));
    return (-10);
}

int open_out_files(t_out_files *files, t_env *env)
{
    int last_fd;
    char *file_name;

    last_fd = 0;
    while (files)
    {
        file_name = ambiguous(files, true, env);
        if (file_name == NULL)
            return (-1);
        // printf("%s\n", file_name);
        if (access(file_name, F_OK) == 0)
        {
            if (access(file_name, W_OK) == 0)
            {
                last_fd = open_file(file_name, files->append, false, true);
                if (last_fd == -1)
                    return (perror("minishell : "), -1);
            }
            else
                return (perror("minishell : "), -1);
        }
        else
        {
            last_fd = open_file(file_name, files->append, true, true);
            if (last_fd == -1)
                return (perror("minishell : "), -1);
        }
        if (files->next)
            close(last_fd);
        files = files->next;
    }
    return (last_fd);
}

int open_in_files(t_in_files *files, t_env *env)
{
    int last_fd;
    char *file_name;

    last_fd = 0;
    while (files)
    {
        file_name = ambiguous(files, false, env);
        if (file_name == NULL)
            return (-1);
        // printf("%s\n", file_name);
        if (access(file_name, F_OK) == 0)
        {
            if (access(file_name, R_OK) == 0)
            {
                last_fd = open_file(file_name, false, false, false);
                if (last_fd == -1)
                    return (perror("minishell : "), -2);
            }
            else
                return (perror("minishell : "), -3);
        }
        else
            return (perror("minishell : "), -4);
        if (files->next)
            close(last_fd);
        files = files->next;
    }
    return (last_fd);
}

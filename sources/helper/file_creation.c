/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:48:34 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 09:25:51 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

int count_spaces(char *ptr)
{
    int i;
    int res = 0;
    i = 0;
    
    while (ptr[i])
    {
        if (ptr[i] == ' ')
            res++;
        i++;
    }
    return (res);
}

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
        if (file1->index_list || file1->wildcard)
            file_name = env_expander(file1->filename, file1->index_list, env, file1->wildcard);
        else
            file_name = file1->filename;
        if (file1->ambiguous || (ft_strchr(file_name, ' ') && count_spaces(file_name) != count_spaces(file1->filename) && file1->wildcard))
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(": ambiguous redirect\n", 2);
            globalVar = 1;
            return (NULL);
        }
        else
            return (file_name);
    }
    else
    {

        file2 = (t_in_files *)files;
        file_name = env_expander(file2->filename, file2->index_list, env, file2->wildcard);
        if (file2->ambiguous || (ft_strchr(file_name, ' ') && count_spaces(file_name) != count_spaces(file2->filename) && file2->wildcard))
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(": ambiguous redirect\n", 2);
            globalVar = 1;
            return (NULL);
        }
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
        if (access(file_name, F_OK) == 0)
        {
            if (access(file_name, W_OK) == 0)
            {
                last_fd = open_file(file_name, files->append, false, true);
                if (last_fd == -1)
                {
                    ft_putstr_fd("minishell : ", 2);
                    ft_putstr_fd(file_name, 2);
                    ft_putstr_fd(" ", 2);
                    ft_putendl_fd(strerror(errno), 2);
                    return -1;
                }
            }
            else
            {
                    ft_putstr_fd("minishell : ", 2);
                    ft_putstr_fd(file_name, 2);
                    ft_putstr_fd(" ", 2);
                    ft_putendl_fd(strerror(errno), 2);
                    return -1;
            }
        }
        else
        {
            last_fd = open_file(file_name, files->append, true, true);
            if (last_fd == -1)
            {
                ft_putstr_fd("minishell : ", 2);
                    ft_putstr_fd(file_name, 2);
                    ft_putstr_fd(" ", 2);
                    ft_putendl_fd(strerror(errno), 2);
                    return -1;
            }
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
        if (access(file_name, F_OK) == 0)
        {
            if (access(file_name, R_OK) == 0)
            {
                last_fd = open_file(file_name, false, false, false);
                if (last_fd == -1)
                {
                    ft_putstr_fd("minishell : ", 2);
                    ft_putstr_fd(file_name, 2);
                    ft_putendl_fd(strerror(errno), 2);
                    return -1;
                }
            }
            else
            {
                ft_putstr_fd("minishell : ", 2);
                ft_putstr_fd(file_name, 2);
                ft_putstr_fd(" ", 2);
                ft_putendl_fd(strerror(errno), 2);
                return -1;
            }
        }
        else
        {
                ft_putstr_fd("minishell : ", 2);
                ft_putstr_fd(file_name, 2);
                ft_putstr_fd(" ", 2);
                ft_putendl_fd(strerror(errno), 2);
                return -1;
        }
        if (files->next)
            close(last_fd);
        files = files->next;
    }
    return (last_fd);
}

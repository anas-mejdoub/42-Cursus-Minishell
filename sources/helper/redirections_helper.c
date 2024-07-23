/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:04:43 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/23 10:15:02 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

int change_rediraction(t_command *cmd ,int *fd_in, int *fd_out)
{
    if (!cmd)
        return (-1);
    if (cmd->dup)
        return (0);
    if (cmd->infd > 0)
    {
        *fd_in = dup(STDIN_FILENO);
        if ((*fd_in) < 0)
            return (-1);
        if (dup2(cmd->infd, STDIN_FILENO) < 0)
            return (-1);
    }
    if (cmd->outfd > 0)
    {
        *fd_out = dup(STDOUT_FILENO);
        if ((*fd_out) < 0)
            return (-1);
        if (dup2(cmd->outfd, STDOUT_FILENO) < 0)
            return (-1);
    }
    return (0);
}

int restor_rediraction(t_command *cmd ,int *fd_in, int *fd_out)
{
    if (!cmd)
        return (-1);
    if (cmd->dup)
        return (0);
    if (cmd->outfd > 0)
    {
        if (dup2(*fd_out, STDOUT_FILENO) < 0)
            return (-1);
        close(*fd_out);
        close(cmd->outfd);
    }
    if (cmd->infd > 0)
    {
        if (dup2(*fd_in, STDIN_FILENO) < 0)
            return (-1);
        close(*fd_in);
        close(cmd->infd);
    }
    return (0);
}
int int_append_to_array(int ***arr, int num, int size)
{
    int **new_arr;
    int *nbr;
    int i = 0;

    new_arr = (int **)malloc((size + 1) * sizeof(int *));
    if (new_arr == NULL)
        return -1;

    while (i < size)
    {
        new_arr[i] = (*arr)[i];
        i++;
    }
    nbr = malloc(sizeof(int));
    *nbr = num;
    new_arr[i] = nbr;
    // if (*arr)
    //     free(*arr);
    *arr = new_arr;
    return (size + 1);
}


bool imbg(t_elem *tmp, t_env *env)
{
    bool err = false;
    char **arr = NULL;
    int **arr_env = ft_calloc(1, 4);
    int index = 0; 
    int size = 0;
    
    while (tmp)
    {
        if (tmp && tmp->type == WORD && tmp->state == GENERAL)
        {
            // if (tmp->content[0])
            // {
                arr = add_to_args(arr, tmp->content);
                index++;
            // }
            tmp = tmp->next;      
        }
        else if (tmp && (tmp->state == IN_DQUOTE || tmp->state == IN_QUOTE))
        {
            // if (tmp->content[0])
            // {     
                arr = add_to_args(arr, tmp->content);
                index++;
            // }
            tmp = tmp->next;
            tmp = tmp->next;
        }
        else if (tmp && (tmp->type == QOUTE || tmp->type == DOUBLE_QUOTE))
        {
            char *a = ft_calloc(1,1);
            tmp = tmp->next;
            while (tmp && (tmp->type != QOUTE && tmp->type != DOUBLE_QUOTE))
            {
                a = ft_strjoin(a, tmp->content);  
                tmp = tmp->next;
            }
            // if (a[0])
            // {       
                arr = add_to_args(arr, a);
                index++;
            // }
            tmp = tmp->next;
        }
        else if (tmp && tmp->type == ENV && tmp->state == GENERAL)
        {
            char *nv = env->get(env->data, (tmp->content + 1));
            if (nv == NULL)
                nv = ft_calloc(1, 1);
            arr = add_to_args(arr, nv);
            size = int_append_to_array(&arr_env, index, size);
            index++;
            tmp = tmp->next;
        }
        else
            break;
    }

    int j = 0;
    while (j < size)
    {
        char *ptr = ft_strtrim(arr[*arr_env[j]], " ");
        // printf("**%s--,%s\n", ptr, arr[*arr_env[j]]);
        if (arr[1] == NULL && (!ptr || ptr[0] == '\0'))
        {
            // printf("0\n");
            err = true;
        }
        else if (arr[*arr_env[j]][0] != '\0' && ft_strchr(ft_strtrim(arr[*arr_env[j]], " ") ,' '))
        {
            // printf("1\n");
            err = true;
        }
        else if (arr[*arr_env[j]][0] == ' ' && *arr_env[j] != 0 && arr[*arr_env[j] - 1] && (arr[*arr_env[j] - 1] && arr[*arr_env[j] - 1][0] != '\0'))
        {
            // printf("2\n");
            err = true;
        }
        else if (arr[*arr_env[j]][0] != '\0' && ft_strlen(arr[*arr_env[j]]) != 0 && arr[*arr_env[j]][ft_strlen(arr[*arr_env[j]]) - 1] == ' ' && arr[*arr_env[j] + 1] && (arr[*arr_env[j] + 1] && arr[*arr_env[j] + 1][0] != '\0'))
        {
            // printf("3\n");
            err = true;
        }
        else if (ft_strlen(arr[*arr_env[j]]) != 0 && arr[*arr_env[j]][ft_strlen(arr[*arr_env[j]]) - 1] == ' ' && j + 1 < size && arr[*arr_env[j + 1]][0] != ' ')
        {
            // printf("3\n");
            err = true;
        }
        if (err)
        {
            // printf("hehe\n");
            break;
        }
        j++;
    }
    // for (int j = 0; arr[j]; j++)
    //     printf("--%s--\n", arr[j]);
    // for (int i = 0; i < size ; i++)
    //     printf("***%d\n", *arr_env[i]);
    // exit(1);
    return (err);
}
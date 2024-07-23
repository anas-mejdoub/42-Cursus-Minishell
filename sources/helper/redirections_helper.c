/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:04:43 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/23 11:41:27 by amejdoub         ###   ########.fr       */
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
            arr = add_to_args(arr, tmp->content);
            index++;
            tmp = tmp->next;      
        }
        else if (tmp && (tmp->state == IN_DQUOTE || tmp->state == IN_QUOTE))
        {
            arr = add_to_args(arr, tmp->content);
            index++;
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
            arr = add_to_args(arr, a);
            index++;
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
        if ((arr[1] == NULL || *arr_env[j] == 0) && (!ptr || (ptr[0] == '\0' && arr[*arr_env[j]][0] == '\0')))
        {
            if (arr[1] == NULL)
                err = true;
            else
            {   
                int u = 0;
                int g = *arr_env[j];
                while (u == g && u < size && arr[u])
                {
                    u++;
                    if (u < size)
                        g = *arr_env[u];
                }
                if (arr[u] == NULL)
                    err = true;
            }
        }
        else if (arr[*arr_env[j]][0] != '\0' && ft_strchr(ft_strtrim(arr[*arr_env[j]], " ") ,' '))
            err = true;
        else if (ft_strlen(arr[*arr_env[j]]) != 0 && arr[*arr_env[j]][ft_strlen(arr[*arr_env[j]]) - 1] == ' ' && j + 1 < size && arr[*arr_env[j + 1]][0] != ' ')

            err = true;
        else if ((arr[*arr_env[j]][0] == ' ' || (ft_strlen(arr[*arr_env[j]]) != 0 && arr[*arr_env[j]][ft_strlen(arr[*arr_env[j]]) - 1] == ' ')))
        {
            int k = *arr_env[j];
            if (ft_strchr(ft_strtrim(arr[*arr_env[j]], " ") ,' '))
            {
                err = true;
                break;
            }
            else if (*arr_env[j] != 0 && (arr[*arr_env[j]][0] == ' ' && ptr[0] != '\0'))
            {
                k--;
                if (ptr[0] == '\0')
                {
                    while (k >= 0 && arr[k][0] == '\0')
                        k--;
                    if (k != 0)
                    {
                        err = true;
                    }      
                }
                while (k >= 0)
                {
                    if (arr[k][0] != '\0')
                    {
                        err = true;
                        break;
                    }
                    k--;
                }
            }
            else if (arr[*arr_env[j]][ft_strlen(arr[*arr_env[j]]) - 1] == ' ' && ptr[0] != '\0')
            {
                k++;
                if (ptr[0] == '\0')
                {
                    while (arr[k] && arr[k][0] == '\0')
                        k++;
                    if (arr[k] == NULL)
                        err = true;   
                }
                else if (arr[*arr_env[j]][ft_strlen(arr[*arr_env[j]]) - 1] == ' ' && ptr[0] != '\0')
                {
                    int o = j;
                    ++o;
                    while (o < size && *arr_env[o] == k && arr[*arr_env[o]] && !ft_strchr(ft_strtrim(arr[*arr_env[o]], " "), ' '))
                    {
                        o++;
                        k++;
                    }
                    while (arr[k] && arr[k][0] == '\0')
                        k++;
                    if (arr[k])
                        err = true;
                }
                while (arr[k])
                {
                    if (arr[k][0] != '\0' && ft_strchr(ft_strtrim(arr[*arr_env[j]], " ") ,' '))
                    {
                        err = true;
                        break;
                    }
                    k++;
                }
            }
            if (arr[*arr_env[j]][ft_strlen(arr[*arr_env[j]]) - 1] == ' ' && ptr[0] == '\0')
            {
                bool p1 = false;
                bool p2 = false;
                int a = *arr_env[j];
                a++;
                while (arr[a])
                {
                    if (arr[a][0] != '\0')
                        break;
                    a++;
                }
                if (!arr[a] || (arr[a] && arr[a][0] == '\0'))
                    p1 = true;
                a = *arr_env[j];
                a--;
                while (*arr_env[j] != 0 && a >= 0)
                {
                    if (arr[a][0] != '\0')
                        break;
                    a--;
                }
                if (a != 0)
                    p2 = true;
                if (p2 == true && p1 == true)
                    err = true;
            }
        }
        if (err)
        {
            break;
        }
        j++;
    }
    return (err);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:05:24 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/28 15:56:51 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

void free_2d_array(char **array)
{
    int i = 0;

    if (array == NULL)
        return;
    while (array && array[i])
    {
        free(array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
    array = NULL;
}

void free_env_index(t_env_index *head)
{
    t_env_index *tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
        tmp = NULL;
    }
    free(head);
    head = NULL;
}
void free_out_files(t_out_files *head)
{
    t_out_files *tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->filename);
        
        if (tmp->index_list)
            free_env_index(tmp->index_list);
        free(tmp);
    }
    free(head);
}

void free_in_files(t_in_files *head)
{
    t_in_files *tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        if (tmp->here_doc)
        {
            // printf("%p\n", tmp->limiter);
            free(tmp->limiter);
        }
        free(tmp->filename);
        if (tmp->index_list)
            free_env_index(tmp->index_list);
        if (tmp->here_doc)
            unlink(tmp->filename);
        free(tmp);
    }
}

void free_command_args(t_command_args *head)
{
    t_command_args *tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        if (tmp->content)
            free(tmp->content);
        if (tmp->index_list)
            free_env_index(tmp->index_list);
        free(tmp);
    }
}

void free_tree(t_command *cmd)
{
    if (!cmd)
        return ;
    free_tree(cmd->right);
    free_tree(cmd->left);
    if (cmd->type_node == NODE)
    { 
        if (cmd->path)
            free(cmd->path);
        if (cmd->command_arg)
            free_command_args(cmd->command_arg);
        if (cmd->outfiles)
            free_out_files(cmd->outfiles);
        if (cmd->in_files)
        {
            
            free_in_files(cmd->in_files);
        }
        if (cmd->args)
        {
            free_2d_array(cmd->args);
            cmd->args = NULL;
        }
    }
    free(cmd);
    cmd = NULL;
}
// void free_tree1(t_command **cmd)
// {
//     if (!*cmd)
//         return ;
//     free_tree1(cmd->right);
//     free_tree1(&((t_command *)(*cmd))->left);
//     if ((*cmd)->type_node  == NODE)
//     { 
//         // if (cmd->path)
//         //     free(cmd->path);
//         // if (cmd->command_arg)
//         //     free_command_args(cmd->command_arg);
//         // if (cmd->outfiles)
//         //     free_out_files(cmd->outfiles);
//         // if (cmd->in_files)
//         //     free_in_files(cmd->in_files);
//         // if (cmd->args)
//         //     free_2d_array(cmd->args);
//         // if (cmd->infile)
//         //     free_2d_array(cmd->infile);
//         // if (cmd->outfile)
//         //     free_2d_array(cmd->outfile);
//     }
//     free(*cmd);
//     *cmd = NULL;
// }
// void free_tree_(t_command **cmd)
// {
//     if (!*cmd)
//         return ;
//     // free_tree((*cmd)->right);
//     // free_tree((*cmd)->left);
//     if ((*cmd)->type_node  == NODE)
//     { 
//         // if (cmd->path)
//         //     free(cmd->path);
//         // if (cmd->command_arg)
//         //     free_command_args(cmd->command_arg);
//         // if (cmd->outfiles)
//         //     free_out_files(cmd->outfiles);
//         // if (cmd->in_files)
//         //     free_in_files(cmd->in_files);
//         // if (cmd->args)
//         //     free_2d_array(cmd->args);
//         // if (cmd->infile)
//         //     free_2d_array(cmd->infile);
//         // if (cmd->outfile)
//         //     free_2d_array(cmd->outfile);
//     }
//     free(*cmd);
//     *cmd = NULL;
//     // free(cmd);
// }
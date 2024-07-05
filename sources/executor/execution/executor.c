/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:39 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/05 10:01:34 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"


char *get_path(char *command, t_env *env)
{
    // printf ("the command is %s\n", command);
    char **paths = ft_split(env->get(env->data, "PATH"), ':');
    int i = 0;
    while (paths[i])
    {
        paths[i] = ft_strjoin(paths[i], "/");
        // printf("-> %s\n", ft_strjoin(paths[i], command));
        if (!access(ft_strjoin(paths[i], command), F_OK))
        {
            // printf("YES\n");
            return (ft_strjoin(paths[i], command));
        }
        i++;
    }
    
    return 0;
}

t_exec_ret *executor(t_command *command, t_env *env, char c)
{
    t_exec_ret *ret;
    t_exec_ret *tmp = NULL;
    ret = malloc(sizeof(t_exec_ret));
    ret->pids = NULL;
    if (!command)
    {
        ret->ret = -1;
        ret->pids = NULL;
        return (ret);
    }
    if (command->type_node == PIPE_LINE_NODE || command->type_node == ROOT_NODE)
    {
        if (command->type_node == PIPE_LINE_NODE )
        {
            int fd[2];
            if (command->outfd != -1)
                ((t_command *)command->left)->outfd = command->outfd;
            int k = pipe(fd);
            if (k == -1)
                exit(99);
            ((t_command *)command->right)->outfd = fd[1];
            ((t_command *)command->left)->infd = fd[0];
        }
        tmp = executor(command->right, env, 'r');

        if (tmp->pids)
        {
            // printf("the next is : %d\n", tmp->ret);
            ret->pids = tmp->pids;
        }
        else
        {
            if (!ret)
                exit(1);
            ret->pids = add_int(ret->pids, tmp->ret);
            // printf("TEST\n");
        }
        // printf("the right %d just finished !\n", tmp->ret);
        // if (command->left)
        // {
            tmp = executor(command->left, env, 'l');
            ret->pids = add_int(ret->pids, tmp->ret);
            // printf("the left %d just finished\n", tmp->ret);
        // }
    }
    // else if (command->type_node == ROOT_NODE)
    // {
    //     printf("in this shit \n");
    //     tmp = executor(command->right, env, '\0');
    //     ret->pids = add_int(ret->pids, tmp->ret);
    // }
    else 
    {
        pid_t i = fork();
        if (i == 0)
        {
        // printf("test : %s c is %c\n", command->command_arg->content, c);
            command->path = get_path(((t_command *)command)->command_arg->content, env);
            // printf("the path is %s --\n", command->path);
            while (command->command_arg)
            {
                command->args = add_to_args(command->args, command->command_arg->content);
                command->command_arg = command->command_arg->next;
            }
            if (c == 'r')
            {
            // execve(command->path, command->args, NULL);
            // ft_printf("THE FUCK RIGHT is %s in %d out %d\n", command->args[0], command->infd, command->outfd);
                dup2(command->outfd, STDOUT_FILENO);
                close(command->outfd);
                close(command->infd);
                execve(command->path, command->args, NULL);
            }
            else if (c == 'l')
            {
                // ft_printf("THE FUCK LEEEEFT is %s in %d out %d\n", command->args[0], command->infd, command->outfd);
                dup2(command->infd, STDIN_FILENO);
                close(command->infd);
                if (command->outfd != -1)
                {
                    // ft_printf("dup is %d and command %s\n", command->outfd, command->args[0]);
                    dup2(command->outfd, STDOUT_FILENO);
                    close(command->outfd);
                    // close();
                }
            // ft_printf("command is %s in %d out %d\n", command->args[0], command->infd, command->outfd);
            execve(command->path, command->args, NULL);
            }
        }
        else if (i > 0)
        {
            
            // printf("PARENT command is %s in %d out %d\n", command->command_arg->content, command->infd, command->outfd);
            // ft_printf("---{}--->\n");
            close(command->outfd);
            close(command->infd);
            if (i == -1)
                ft_printf("something wrong !-----------\n");
            // ft_printf("i is %d\n", i);
            ret->ret = i;
            ret->pids = NULL;
            return (ret);
        }
        else if (i < 0)
            printf("THE FORK FAILED ! \n");
    }
    // int l= 0;
    // while (ret->pids[l])
    // {
    //     printf("checking %s the pids %d\n",((t_command *)command->right)->command_arg->content, ret->pids[l]);
    //     l++;
    // }
    // close(command->infd);
    // close(command->outfd);
    // if (!ret)
    //     printf("NUUUUUUUULLLLL\n");
    return (ret);
}

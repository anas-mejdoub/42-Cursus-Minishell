/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:39 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/04 11:36:22 by amejdoub         ###   ########.fr       */
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
    t_exec_ret *ret = NULL;
    ret = malloc(sizeof(t_exec_ret));
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
            int k = pipe(fd);
            if (k == -1)
                exit(99);
            ((t_command *)command->right)->outfd = fd[1];
            ((t_command *)command->left)->infd = fd[0];
        }
        t_exec_ret *tmp = executor(command->right, env, 'r');
        ret->pids = add_int(ret->pids, tmp->ret);
        // printf ("the return of right is, tmp->ret");
        tmp = executor(command->left, env, 'l');
        ret->pids = add_int(ret->pids, tmp->ret);
        
    }
    else if (command->type_node == ROOT_NODE)
        executor(command->right, env, '\0');
    else 
    {
        pid_t i = fork();
        if (i == 0)
        {
            command->path = get_path(((t_command *)command)->command_arg->content, env);
            while (command->command_arg)
            {
                command->args = add_to_args(command->args, command->command_arg->content);
                command->command_arg = command->command_arg->next;
            }
            if (c == 'r')
            {
                dup2(command->outfd, STDOUT_FILENO);
            }
            else if (c == 'l')
            {
                dup2(command->infd, STDIN_FILENO);
            }
            execve(command->path, command->args, NULL);
        }
        else
        {
            printf("---{}--->\n");
            close(command->outfd);
            close(command->infd);
            if (i == -1)
                printf("something wrong !-----------\n");
            // printf("i is %d\n", i);
            ret->ret = i;
            ret->pids = NULL;
            return (ret);
        }
    }
    // int l= 0;
    // while (ret->pids[l])
    // {
    //     printf("checking the pids %d\n", ret->pids[l]);
    //     l++;
    // }
    return (ret);
}
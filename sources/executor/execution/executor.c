/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:39 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/09 10:40:51 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

#include <signal.h>
#include <stdio.h>


char	*ft_freed_join(char *s1, char *s2)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && *s2)
	{
		res[i] = *s2;
		s2++;
		i++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}

char *get_path(char *command, t_env *env)
{
    char **paths;
    int i;
    char *tmp;
    char *tmp2;

    if (!command[0] || !env || !env->data)
        return NULL;
    paths = ft_split(env->get(env->data, "PATH"), ':');
    if (!paths)
        return (NULL);
    i = 0;
    tmp = NULL;
    tmp2 = NULL;
    while (paths[i])
    {
        tmp = ft_freed_join(paths[i], "/");
        tmp2 = ft_freed_join(tmp, command);
        if (!access(tmp2, F_OK) && access(tmp2, X_OK) == -1)
        {
            ft_putstr_fd("minishell : Permission denied\n", 2);
            exit(126);
            return NULL;
        }
        if (!access(tmp2, F_OK))
            return (tmp2);
        i++;
        free(tmp2);
        tmp2 = NULL;
    }
    if (!access(command, F_OK) && access(command, X_OK) == -1)
        {
            ft_putstr_fd("minishell : Permission denied\n", 2);
            exit(126);
            return NULL;
        }
    if (!access(command, F_OK))
        return (command);
    return 0;
}
char **get_command_args(t_command_args *args, t_env *env)
{
    char **res;
    char *tmp_str;
    char **tmp_arr;
    res = NULL;
    while (args)
    {
        tmp_str = env_expander(args->content, args->index_list, env);
        if (ft_strchr(tmp_str, ' ') && args->env)
        {
            tmp_arr = ft_split(tmp_str, ' ');
            int i = 0;
            while (tmp_arr[i])
            {
                res = add_to_args(res, tmp_arr[i]);
                i++;
            }
        }
        else
            res = add_to_args(res, tmp_str);
        args = args->next;
    }
    return (res);
}
void handle_intr_sig(int sig)
{
    (void)sig;
}
t_exec_ret *executor(t_command *command, t_env *env, char c, char **ev)
{
    t_exec_ret *ret;
    t_exec_ret *tmp = NULL;
    bool found_in = false;
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
        if (command && command->right && is_builtin(command->right) && !command->left)
            executor(command->right, env, 'b', ev);
        else if (command && command->right)
            tmp = executor(command->right, env, 'r', ev);
        if (tmp && tmp->pids)
            ret->pids = tmp->pids;
        else if (tmp && tmp->ret != -1)
            ret->pids = add_int(ret->pids, tmp->ret);
        tmp = executor(command->left, env, 'l', ev);
        ret->pids = add_int(ret->pids, tmp->ret);
    }
    else 
    {
        command->args = get_command_args(command->command_arg, env);
            if (command->in_files)
            {
                command->infd = open_in_files(command->in_files, env);
                if (command->infd < 0)
                {
                    found_in = true;
                   globalVar = 1;
                }
            }
            if (command->outfiles && !found_in)
            {
                command->outfd = open_out_files(command->outfiles, env);
                if (command->outfd < 0)
                {
                   globalVar = 1;
                    
                }    
            }
        if (c == 'b')
        {
            if (do_builtin(command, env) == -1)
                globalVar = 1;
            else
                globalVar = 0;
            ret->ret = -1;
            return ret;
        }
        signal (SIGINT, SIG_IGN);
        globalVar = 0;
        pid_t i = fork();
        signal (SIGINT, handle_intr_sig);
        if (i == 0)
        {
            if (command->command_arg)
                command->path = get_path(command->args[0], env);
            if (found_in)
                exit(1);
            if (command->command_arg && !command->path && !is_builtin(command) && access(command->args[0], F_OK))
            {
                
                printf("minishell: ");
                printf("%s", command->args[0]);
                printf(": command not found\n");
                exit (127);
            }
            if (  !command->path && !is_builtin(command) && command->command_arg && !access(command->args[0], F_OK) && access(command->args[0], X_OK))
            {
                printf("minishell :  Permission denied\n");
                exit(126);
                return NULL;
            }
            // if (command->outfiles)
            // {
            //     command->outfd = open_out_files(command->outfiles, env);
            //     if (command->outfd < 0)
            //         exit(1);
            // }
            // if (command->in_files)
            // {
            //     command->infd = open_in_files(command->in_files, env);
            //     if (command->infd < 0)
            //         exit(1);
            // }
            dup2(command->outfd, STDOUT_FILENO);
            if (command->infd != -1)
                dup2(command->infd, STDIN_FILENO);
            close(command->outfd);
            close(command->infd);
            if (!command->path && !command->args)
                exit(0);
            if (is_builtin(command))
            {
                if (do_builtin(command, env) == -1)
                    exit(1);
                exit(0);
            }
            if (execve(command->path, command->args, env_to_2d_arr(env)) == -1)
            {
                perror("execve : ");
                exit(127);
            }
        }
        else if (i > 0)
        {
            close(command->outfd);
            close(command->infd);
            if (i == -1)
                ft_printf("something wrong !\n");
            ret->ret = i;
            ret->pids = NULL;
            return (ret);
        }
        else if (i < 0)
            printf("THE FORK FAILED ! \n");
    }
    return (ret);
}

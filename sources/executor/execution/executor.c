/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:39 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/21 11:14:54 by amejdoub         ###   ########.fr       */
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
void close_fds(int *arr)
{
    int i = 0;
    while (arr)
    {
        if (arr[i] == -1)
            break;
        close (arr[i]);
        i++;
    }
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
    {
        if (!access(command, F_OK))
            return command;
        return (NULL);
    }
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
    if (!access(command, F_OK) && command[0] == '.' && command[1] && command[1] == '/')   {
        return (command);
    }
    return 0;
}
char **get_command_args(t_command_args *args, t_env *env)
{
    int fd[2];
    
    fd[0] = -1;
    fd[1] = -1;
    char **res;
    char *tmp_str;
    char **tmp_arr;
    res = NULL;
    while (args)
    {
        tmp_str = env_expander(args->content, args->index_list, env);
        if (tmp_str == NULL)
        {
            args = args->next;
            continue; 
        }
            
        // printf("%d\n", args->including_null);
        if (tmp_str[0] == '\0' && args->index_list && !args->including_null)
        {
            // ft_putendl_fd(tmp_str, 2);
            args = args->next;
            continue;
        }
        if (ft_strchr(tmp_str, ' ') && args->env)
        {
            tmp_arr = ft_split(tmp_str, ' ');
            int i = 0;
            while (tmp_arr[i])
            {
                // if (tmp_arr[i] == '\0')
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
            int status;
    int fd[2];
    fd[0] = -1;
    fd[1] = -1;
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
    if (command->type_node == AND_NODE)
    {
        if (command->outfd != -1)
            ((t_command *)command->left)->outfd = command->outfd;
        if (command->infd != -1)
            ((t_command *)command->right)->infd = command->infd;
        ((t_command *)command->left)->fd[0] = fd[0];
        ((t_command *)command->left)->fd[1] = fd[1];
        ((t_command *)command->right)->fd[0] = fd[0];
        ((t_command *)command->right)->fd[1] = fd[1];
        tmp = executor(command->right, env, 'r', ev);
        // if (!tmp)
        //     return NULL;
        if (tmp && tmp->pids)
        {
            // printf("first\n");
            int ir = 0;
            while (tmp && tmp->pids)
            {
                if (tmp->pids[ir] == -1)
                    break;
                waitpid(tmp->pids[ir], &status, 0);
                if (WIFEXITED(status))
                    globalVar = WEXITSTATUS(status);
                else if (WIFSIGNALED(status))
                {

                // printf ("signaled\n");
                    globalVar = WTERMSIG(status) + 128;
                }
                ir++;
            }
            ret->pids = tmp->pids;
            // printf("global is %d\n",globalVar);
        }
        else if (tmp && tmp->ret != -1)
        {
            // printf("secoond\n");
            waitpid(tmp->ret, &status, 0);
            if (WIFEXITED(status))
                globalVar = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                globalVar = WTERMSIG(status) + 128;
            ret->pids = add_int(ret->pids, tmp->ret);
        }
        // printf ("the global var is %d\n", globalVar);
        if (globalVar == 0)
        {
            // if (!command->left )
            //     printf("NULLLLL\n");
            if (((t_command *)command->left)->command_arg)
                printf("the command is %s\n", ((t_command *)command->left)->command_arg->content);
            tmp = executor(command->left, env, 'l', ev);
            if (!tmp)
                return NULL;
            if (tmp && tmp->pids)
                ret->pids = tmp->pids;
            else if (tmp && tmp->ret != -1)
                ret->pids = add_int(ret->pids, tmp->ret);
        }
        else
            return NULL;
        return (ret);
    }
    if (command->type_node == OR_NODE)
    {
        if (command->outfd != -1)
            ((t_command *)command->left)->outfd = command->outfd;
        if (command->infd != -1)
            ((t_command *)command->right)->infd = command->infd;
        ((t_command *)command->left)->fd[0] = fd[0];
        ((t_command *)command->left)->fd[1] = fd[1];
        ((t_command *)command->right)->fd[0] = fd[0];
        ((t_command *)command->right)->fd[1] = fd[1];
        tmp = executor(command->right, env, 'r', ev);
        // if (!tmp)
        //     return NULL;
        if (tmp && tmp->pids)
        {
            int ir = 0;
            while (tmp && tmp->pids)
            {
                if (tmp->pids[ir] == -1)
                    break;
                waitpid(tmp->pids[ir], &status, 0);
                if (WIFEXITED(status))
                    globalVar = WEXITSTATUS(status);
                else if (WIFSIGNALED(status))
                {

                    globalVar = WTERMSIG(status) + 128;
                }
                ir++;
            }
            ret->pids = tmp->pids;
        }
        else if (tmp && tmp->ret != -1)
        {
            waitpid(tmp->ret, &status, 0);
            if (WIFEXITED(status))
                globalVar = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
            {
                globalVar = WTERMSIG(status) + 128;
            }
            ret->pids = add_int(ret->pids, tmp->ret);
        }
        // printf ("inside the or the global var is %d\n", globalVar);
        if (globalVar != 0)
        {
            // printf ("hjgxfhdghg\n");
            tmp = executor(command->left, env, 'l', ev);
            if (!tmp)
                return NULL;
            if (tmp && tmp->pids)
                ret->pids = tmp->pids;
            else if (tmp && tmp->ret != -1)
                ret->pids = add_int(ret->pids, tmp->ret);
        }
        else
            return NULL;
        return (ret);
    }
    if (command->type_node == PIPE_LINE_NODE || command->type_node == ROOT_NODE)
    {
        if (command->type_node == PIPE_LINE_NODE )
        {
            ((t_command *)command->left)->to_close = add_int(command->to_close, command->fd[0]);
            ((t_command *)command->right)->to_close = add_int(command->to_close, command->fd[0]);
            if (command->outfd != -1)
            {
                ((t_command *)command->left)->outfd = command->outfd;
            }
            if (command->infd != -1)
                ((t_command *)command->right)->infd = command->infd;
            int k = pipe(fd);
            ((t_command *)command->left)->fd[0] = fd[0];
            ((t_command *)command->left)->fd[1] = fd[1];
            ((t_command *)command->right)->fd[0] = fd[0];
            ((t_command *)command->right)->fd[1] = fd[1];
            if (k == -1)
            {
                close(fd[1]);
                close(fd[0]);
                ft_putstr_fd("minishell fork : Resource temporarily unavailable\n", 2);
                globalVar = 1;
                return NULL;
            }
            ((t_command *)command->right)->outfd = fd[1];
            ((t_command *)command->left)->infd = fd[0];
        }
        if (command && command->right && is_builtin(command->right) && !command->left)
            tmp = executor(command->right, env, 'b', ev);
        else if (command && command->right)
            tmp = executor(command->right, env, 'r', ev);
        close (fd[1]);
        if (!tmp)
        {
            close(fd[1]);
            close(fd[0]);
            return NULL;
        }
        if (tmp && tmp->pids)
            ret->pids = tmp->pids;
        else if (tmp && tmp->ret != -1)
            ret->pids = add_int(ret->pids, tmp->ret);
        tmp = executor(command->left, env, 'l', ev);
        close(fd[0]);
        if (!tmp)
        {
            close(fd[1]);
            close(fd[0]);
            return NULL;
        }
        ret->pids = add_int(ret->pids, tmp->ret);
    }
    else if (command->type_node == SUBSHELL_NODE)
    {
        // printf ("subshell entered\n");
        ((t_command *)command->right)->to_close = add_int(command->to_close, command->fd[0]);
        ((t_command *)command->right)->fd[0] = command->fd[0];
        ((t_command *)command->right)->fd[1] = command->fd[1];
        
        // while (command->outfiles)
        // {
        //     printf("%s\n", command->outfiles->filename);
        //     command->outfiles = command->outfiles->next;
        // }
        command->to_close = add_int(command->to_close, command->fd[0]);
        // printf("the first is %d\n", command->to_close[0]);
        if (command->outfd != -1)
        {
            ((t_command *)command->right)->outfd = command->outfd;
        }
        if (command->infd != -1)
        {
            ((t_command *)command->right)->infd = command->infd;
        }
        if (command->in_files)
            {
                ((t_command *)command->right)->infd = open_in_files(command->in_files, env);
                if (((t_command *)command->right)->infd < 0)
                {
                    found_in = true;
                    globalVar = 1;
                }
            }
            if (command->outfiles && !found_in)
            {
                ((t_command *)command->right)->outfd = open_out_files(command->outfiles, env);
                if (((t_command *)command->right)->outfd < 0)
                {
                    globalVar = 1;
                }    
            }
        int f = fork();
        if (f == 0)
        {
            ret = executor(command->right, env, 'r', ev);
            int kk = 0;
            if (ret && ret->pids)
            {
                int eter = 0;
                while (1)
                {
                    if (ret->pids[eter] == -1)
                        break;
                    waitpid(ret->pids[eter], &kk, 0);
                    if (WIFEXITED(kk))
                        globalVar = WEXITSTATUS(kk);
                    else if (WIFSIGNALED(kk))
                        globalVar = WTERMSIG(kk) + 128;
                    eter++;
                }
            }
            else if (ret && ret->ret != -1)
            {
                waitpid(ret->ret, &kk, 0);
                if (WIFEXITED(kk))
                        globalVar = WEXITSTATUS(kk);
                else if (WIFSIGNALED(kk))
                        globalVar = WTERMSIG(kk) + 128;
            }
            close(command->outfd);
            exit (globalVar);
        }
        else if (f > 0)
        {
            int hh = 0;
            // waitpid(f, &hh, 0);
            close(command->outfd);
            close(command->infd);
            if (c == 'r')
                close(command->fd[1]);
            if (c == 'l')
                close(command->fd[0]);
            globalVar = WEXITSTATUS(hh);
            ret->ret = f;
            ret->pids = NULL;
            return (ret);
        }
    }
    else if (command->type_node == NODE)
    {
        command->args = get_command_args(command->command_arg, env);
        if (command->args == NULL)
        {
            return (NULL);
        }
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
            if ((command->outfiles && command->outfd == -1) || (command->infd && found_in == true) || do_builtin(command, env) == -1)
                globalVar = 1;
            else
                globalVar = 0;
            ret->ret = -1;
            return ret;
        }
        signal (SIGINT, SIG_IGN);
        globalVar = 0;
        
        pid_t i = fork();
        if (i < 0)
        {
            ft_putstr_fd("minishell fork : Resource temporarily unavailable\n", 2);
            globalVar = 1;
            return (NULL);
        }
        signal (SIGINT, handle_intr_sig);
        if (i == 0)
        {
            signal(SIGQUIT, SIG_DFL);
            if (command->command_arg)
                command->path = get_path(command->args[0], env);
            if ((command->outfiles && command->outfd == -1) || (command->infd && found_in == true))
                exit(1);
            if (command->command_arg && !command->path && !is_builtin(command) && access(command->args[0], F_OK))
            {
                
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(command->args[0], 2);
                ft_putstr_fd(": command not found\n", 2);
                exit (127);
            }
            if (!command->path && !is_builtin(command) && command->command_arg && !access(command->args[0], F_OK) && access(command->args[0], X_OK))
            {
                ft_putstr_fd("minishell :  Permission denied\n", 2);
                exit(126);
                return NULL;
            }
            if (command->outfd != -1)
                dup2(command->outfd, STDOUT_FILENO); //changed
            if (command->infd != -1)
                dup2(command->infd, STDIN_FILENO); // changed 
            if (c == 'r')
            {
                
                close(command->fd[0]);
                if (command->to_close != NULL)
                    close_fds(command->to_close);
            }
            if (c == 'l')
            {
                if (command->to_close != NULL)
                    close_fds(command->to_close);
                close(command->fd[1]);
            }
            close(command->outfd);
            close(command->infd);
            if (!command->path && !command->args)
                exit(0);
            if (is_builtin(command))
            {
                if ((command->outfiles && command->outfd == -1) || (command->infd && found_in == true)  || do_builtin(command, env) == -1)
                    exit(1);
                exit(0);
            }
            // for (int a = 0; command->args[a]; a++)
            // {
            //     ft_putendl_fd("hhhh",2);
            //     ft_putendl_fd(command->args[a],2);
            //     ft_putendl_fd("hhhh",2);
            // }
            if (execve(command->path, command->args, env_to_2d_arr(env)) == -1)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(command->args[0], 2);
                ft_putstr_fd(": command not found\n", 2);
                exit(127);
            }
        }
        else if (i > 0)
        {
            close(command->outfd);
            close(command->infd);
            if (c == 'r')
                close(command->fd[1]);
            if (c == 'l')
            {
                close(command->fd[0]);
            }
            ret->ret = i;
            ret->pids = NULL;
            return (ret);
        }
    }
    return (ret);
}

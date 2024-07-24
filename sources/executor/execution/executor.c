/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:39 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/24 12:09:20 by amejdoub         ###   ########.fr       */
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
    if (!access(command, F_OK) && ( (command[0] == '.' && command[1]) || command[0] == '/'))
    {
        return (command);
    }
    // printf ("not found\n");
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
        tmp_str = env_expander(args->content, args->index_list, env, args->wildcard);
        if (tmp_str == NULL)
        {
            args = args->next;
            continue; 
        }   
        if (tmp_str[0] == '\0' && args->index_list && !args->including_null)
        {
            args = args->next;
            continue;
        }
        if (ft_strchr(tmp_str, ' ') && (args->env || args->wildcard))
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

t_exec_ret * and_node(t_command *command, char **ev, t_exec_ret *ret, t_env *env)
{
    // bool found_in = false;
    t_exec_ret *tmp = NULL;
    int  status = 0;
    if (command->outfd != -1)
    {
        ((t_command *)command->right)->outfd = command->outfd;
        ((t_command *)command->left)->outfd = dup(command->outfd);
    }
    if (command->infd != -1)
    {
        ((t_command *)command->right)->infd = command->infd;
        ((t_command *)command->left)->infd = dup(command->infd);
    }
    ((t_command *)command->left)->fd[0] = command->fd[0];
    ((t_command *)command->left)->fd[1] = command->fd[1];
    ((t_command *)command->right)->fd[0] = command->fd[0];
    ((t_command *)command->right)->fd[1] = command->fd[1];
    tmp = executor(command->right, env, '\0', ev);
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
        globalVar = WTERMSIG(status) + 128;
        ret->pids = add_int(ret->pids, tmp->ret);
    }
    if (globalVar == 0)
    {
        tmp = executor(command->left, env, '\0', ev);
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

t_exec_ret *or_node(t_command *command, char **ev, t_exec_ret *ret, t_env *env)
{
    t_exec_ret *tmp = NULL;
    int  status = 0;
    if (command->outfd != -1)
    {
        ((t_command *)command->left)->outfd = command->outfd;
        ((t_command *)command->right)->outfd = command->outfd;
    }
    if (command->infd != -1)
    {
        ((t_command *)command->right)->infd = command->infd;
        ((t_command *)command->left)->infd =dup(command->infd);

    }
    ((t_command *)command->left)->fd[0] = command->fd[0];
    ((t_command *)command->left)->fd[1] = command->fd[1];
    ((t_command *)command->right)->fd[0] = command->fd[0];
    ((t_command *)command->right)->fd[1] = command->fd[1];
    tmp = executor(command->right, env, '\0', ev);
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
    if (globalVar != 0)
    {
        tmp = executor(command->left, env, '\0', ev);
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

bool pipeline_node(t_command **command, char **ev, t_exec_ret *ret, t_env *env)
{
    int fd[2];
    t_exec_ret *tmp = NULL;
    fd[0] = -1;
    fd[1] = -1;
    if ((*command)->type_node == PIPE_LINE_NODE)
    {
        ((t_command *)(*command)->left)->to_close = add_int((*command)->to_close, (*command)->fd[0]);
        ((t_command *)(*command)->right)->to_close = add_int((*command)->to_close, (*command)->fd[0]);
        if ((*command)->outfd != -1)
        {
        ((t_command *)(*command)->left)->outfd = (*command)->outfd;
        }
        if ((*command)->infd != -1)
        ((t_command *)(*command)->right)->infd = (*command)->infd;
        int k = pipe(fd);
        ((t_command *)(*command)->left)->fd[0] = fd[0];
        ((t_command *)(*command)->left)->fd[1] = fd[1];
        ((t_command *)(*command)->right)->fd[0] = fd[0];
        ((t_command *)(*command)->right)->fd[1] = fd[1];
        if (k == -1)
        {
        close(fd[1]);
        close(fd[0]);
        ft_putstr_fd("minishell fork : Resource temporarily unavailable\n", 2);
        globalVar = 1;
        return false;
        }
        ((t_command *)(*command)->right)->outfd = fd[1];
        ((t_command *)(*command)->left)->infd = fd[0];
    }
    if ((*command) && (*command)->right && is_builtin((*command)->right) && !(*command)->left)
        tmp = executor((*command)->right, env, 'b', ev);
    else if ((*command) && (*command)->right)
        tmp = executor((*command)->right, env, 'r', ev);
    close (fd[1]);
    if (!tmp)
    {
        close(fd[1]);
        close(fd[0]);
        return false;
    }
    if (tmp && tmp->pids)
        ret->pids = tmp->pids;
    else if (tmp && tmp->ret != -1)
        ret->pids = add_int(ret->pids, tmp->ret);
    tmp = executor((*command)->left, env, 'l', ev);
    close(fd[0]);
    if (!tmp)
    {
        close(fd[1]);
        close(fd[0]);
        return false;
    }
    ret->pids = add_int(ret->pids, tmp->ret);
    return (true);
}

t_exec_ret *executor(t_command *command, t_env *env, char c, char **ev)
{
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
        return (and_node(command, ev, ret, env));
    }
    if (command->type_node == OR_NODE)
    {
        return (or_node(command, ev, ret, env));
    }
    if (command->type_node == PIPE_LINE_NODE || command->type_node == ROOT_NODE)
    {
        if (!pipeline_node(&command, ev, ret, env))
            return (NULL);
    }
    else if (command->type_node == SUBSHELL_NODE)
    {
        ((t_command *)command->right)->to_close = add_int(command->to_close, command->fd[0]);
        ((t_command *)command->right)->fd[0] = command->fd[0];
        ((t_command *)command->right)->fd[1] = command->fd[1];
        
        if (command->in_files)
        {
                command->infd = open_in_files(command->in_files, env);
                if (command->infd < 0)
                {
                    found_in = true;
                    globalVar = 1;
                return (NULL);
                }
        }
        if (command->outfiles && !found_in)
        {
                command->outfd = open_out_files(command->outfiles, env);
                if (command->outfd < 0)
                {
                    globalVar = 1;
                return NULL;
                }
        }
        command->to_close = add_int(command->to_close, command->fd[0]);
        if (command->outfd != -1)
        {
            ((t_command *)command->right)->outfd = command->outfd;
        }
        if (command->infd != -1)
        {
            ((t_command *)command->right)->infd = command->infd;
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
            close_fds(((t_command *)command)->to_close);
            close_fds(((t_command *)command->right)->to_close);
            if (c == 'r')
            {
                close(command->fd[1]);
                close(((t_command *)command->right)->fd[1]);

            }
            if (c == 'l')
            {
                close(command->fd[0]);
                close(((t_command *)command->right)->fd[0]);

            }
            // close_fds(((t_command *)command->right)->to_close);
            close(((t_command *)command->right)->outfd);
            close(((t_command *)command->right)->infd);
            close(((t_command *)command)->outfd);
            close(((t_command *)command)->infd);
            exit (globalVar);
        }
        else if (f > 0)
        {
            int hh = 0;
            if (!c)
            {
                close(command->outfd);
                close(command->infd);
                close(((t_command *)command->right)->outfd);;
                close(((t_command *)command->right)->infd);
            }
            // close_fds(((t_command *)command->right)->to_close);
            // close(((t_command *)command->right)->outfd);
            // close(((t_command *)command->right)->infd);
            // close(command->outfd);
            // close(command->infd);
            if (c == 'r')
            {
                // printf("yes \n");
                close(((t_command *)command->right)->outfd);;
                close(command->outfd);
                close(command->fd[1]);
                close(((t_command *)command->right)->fd[1]);

            }
            if (c == 'l')
            {
                close(command->fd[0]);
                close(command->infd);
                close(((t_command *)command->right)->fd[0]);
                close(((t_command *)command->right)->infd);

            }
            globalVar = WEXITSTATUS(hh);
            ret->ret = f;
            ret->pids = NULL;
            return (ret);
        }
    }
    else if (command->type_node == NODE)
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
        if (command->args == NULL)
        {
            return (NULL);
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
            {
                exit(1);
            }
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
            {
                dup2(command->outfd, STDOUT_FILENO);
                command->dup = true;
            }
            if (command->infd != -1)
            {
                command->dup = true;
                dup2(command->infd, STDIN_FILENO);
                
            }
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
            if (!c)
            {
                close(command->outfd);
                close(command->infd);
            }
            if (c == 'r')
            {
                close(command->outfd);
                close(command->fd[1]);
            }
            if (c == 'l')
            {
                close(command->infd);
                close(command->fd[0]);
            }
            ret->ret = i;
            ret->pids = NULL;
            return (ret);
        }
    }
    return (ret);
}

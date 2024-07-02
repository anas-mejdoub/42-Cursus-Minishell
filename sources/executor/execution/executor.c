/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:39 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/02 16:30:06 by amejdoub         ###   ########.fr       */
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

void executor(t_command *command, t_env *env)
{
    if (command->type_node == PIPE_LINE_NODE)
    {
        
    }
    if (command->type_node != NODE)
        executor(command->right, env);
    
    else 
    {
        pid_t i = fork();
        if (i == 0)
        {
            command->path = get_path(((t_command *)command)->command_arg->content, env);
            // char **args = NULL;
            while (command->command_arg)
            {
                command->args = add_to_args(command->args, command->command_arg->content);
                command->command_arg = command->command_arg->next;
            }
            execve(command->path, command->args, NULL);        
        }
        else
        {
            waitpid(i, NULL, 0);
        }
    }
}
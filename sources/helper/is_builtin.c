/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:27:05 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/07 14:47:29 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"
int is_builtin(t_command *cmd)
{
    if ((!ft_strncmp(cmd->command_arg->content, "export", ft_strlen(cmd->command_arg->content)) && ft_strlen(cmd->command_arg->content) == ft_strlen("export")))
        return (1);
    else if ((!ft_strncmp(cmd->command_arg->content, "env", ft_strlen(cmd->command_arg->content)) && ft_strlen(cmd->command_arg->content) == ft_strlen("env")))
        return (1);
    else if ((!ft_strncmp(cmd->command_arg->content, "echo", ft_strlen(cmd->command_arg->content)) && ft_strlen(cmd->command_arg->content) == ft_strlen("echo")))
        return (1);
    else if ((!ft_strncmp(cmd->command_arg->content, "exit", ft_strlen(cmd->command_arg->content)) && ft_strlen(cmd->command_arg->content) == ft_strlen("exit")))
        return (1);
    return (0);
    // else if ((!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("cd")))
    // esle if ((!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("pwd")))
    // else if ((!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("pwd")))

}
int do_builtin(t_command *cmd, t_env *env)
{
    if ((!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("export")))
    {
        if (export_cmd(cmd, env) == -1)
            return (-1);
        // printf("TEEES\n");
        return (1);
    }
    else if ((!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("env")))
    {   
        if (env_cmd(cmd, env) == -1)
            return (-1);
        return (1);
    }
    else if ((!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("echo")))
    {
        if (echo_cmd(cmd) == -1)
            return (-1);
        return (1);
    }
    else if ((!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("exit")))
    {
        if (exit_comand(cmd) == -1)
            return (-1);
        return (1);
    }
    // else if ((!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("cd")))
    // esle if ((!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("pwd")))
    // else if ((!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("pwd")))
    return (0);

}
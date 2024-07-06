/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 09:58:21 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/06 11:24:21 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

// int change_rediraction(t_command *cmd ,int *fd_in, int *fd_out)
// {
//     //change rediraction in
//     if (cmd->infd)
//     {
//         *fd_in = dup(STDIN_FILENO);
//         if ((*fd_in) < 0)
//             return (-1);
//         if (dup2(cmd->infd, STDIN_FILENO) < 0)
//             return (-1);
//     }
//     //change rediraction out
//     if (cmd->outfd)
//     {
//         *fd_out = dup(STDOUT_FILENO);
//         if ((*fd_out) < 0)
//             return (-1);
//         if (dup2(cmd->outfd, STDOUT_FILENO) < 0)
//             return (-1);
//     }
//     return (0);
// }

// int restor_rediraction(t_command *cmd ,int *fd_in, int *fd_out)
// {
//     //restor rediraction out
//     if (cmd->outfd)
//     {
//         if (dup2(*fd_out, STDOUT_FILENO) < 0)
//             return (-1);
//         clode(*fd_out);
//     }
//     //restor rediraction in
//     if (cmd->infd)
//     {
//         if (dup2(*fd_in, STDIN_FILENO) < 0)
//             return (-1);
//         clode(*fd_in);
//     }
//     return (0);
// }

int echo_cmd(t_command *cmd, t_env *env)
{
    // char *echo;
    // int fd_in;
    // int fd_out;
    // int std_in;
    // int std_out;
    
    
    
    // echo = env_expander(cmd->command_arg->content, cmd->command_arg->index_list, env);

    // if (!(!ft_strncmp(echo, "echo", ft_strlen(echo)) && ft_strlen(echo) == ft_strlen("echo")))
    //     return (-1);
    // cmd->args = ((t_command_args *)cmd->args)->next;
    // if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
    //     return (-1);

    

    // if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
    //     return (-1);

    

    




    return (0);
}

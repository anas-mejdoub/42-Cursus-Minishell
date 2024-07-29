/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:04:43 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 08:42:05 by nbenyahy         ###   ########.fr       */
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

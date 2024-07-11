/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 09:58:21 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/11 11:10:36 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"


int echo_cmd(t_command *cmd)
{
    int fd_in;
    int fd_out;
    int new_line;
    int i;

    new_line = 1;
    i = 1;

    if (cmd->args && !(!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("echo")))
        return (-1);
    if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    while (cmd->args && cmd->args[i] && cmd->args[i][0] && cmd->args[i][0] == '-')
    {
        if (cmd->args && cmd->args[i] && cmd->args[i][0] == '-' && cmd->args[i][1])
        {
            char *str = ft_strtrim(cmd->args[i] +  1, "n");
            if (str[0] == '\0')
            {
                new_line = 0;
                // i++;
            }
        }
        i++;
    }
    while (cmd->args && cmd->args[i])
    {
        printf("%s", cmd->args[i]);
        i++;
        if (cmd->args[i])
            printf(" ");
    }
    if (new_line)
        printf("\n");
    if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    return (0);
}

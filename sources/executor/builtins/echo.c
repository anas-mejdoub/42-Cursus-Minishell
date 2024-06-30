/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 09:58:21 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/30 10:36:16 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int echo(t_command *cmd)
{
    int new_line;
    int i;

    i = 0;
    new_line = 1;
    if (!cmd || !cmd->command_args)
        return (1);
    if (!ft_strncmp(cmd->command_args[i], "echo", ft_strlen("echo")) && ft_strlen("echo") == ft_strlen(cmd->command_args[i]))
        i++;
    else
        return (1);
    if (!ft_strncmp(cmd->command_args[i], "-n", ft_strlen("-n")) && ft_strlen("-n") == ft_strlen(cmd->command_args[i]))
    {
        new_line = 0;
        i++;
    }
    while (cmd && cmd->command_args && cmd->command_args[i])
    {
        printf("%s", cmd->command_args[i]);
        i++;
        if (cmd->command_args[i])
            printf(" ");
    }
    if (new_line == 1)
        printf("\n");
    return (0);
}

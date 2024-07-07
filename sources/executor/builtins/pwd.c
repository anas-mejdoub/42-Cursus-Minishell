/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:46:05 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/07 16:53:48 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int   pwd_cmd(t_command *cmd)
{
    char tmp[1024];
    char *ptr;

    if (cmd->args && !(!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("pwd")))
		return (-1);
    ptr = getcwd(tmp, 1024);
    if (!ptr)
        perror("minishell :");
    printf("%s\n", ptr);
    return (1);
}

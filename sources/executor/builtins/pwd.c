/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:46:05 by nbenyahy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/11 15:58:36 by amejdoub         ###   ########.fr       */
=======
/*   Updated: 2024/07/11 16:09:24 by amejdoub         ###   ########.fr       */
>>>>>>> exec
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int   pwd_cmd(t_command *cmd)
{
    char tmp[1024];
    char *ptr;
        int fd_in;
    int fd_out;

    if (cmd->args && !(!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("pwd")))
		  return (-1);
    if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
      return (-1);
    ptr = getcwd(tmp, 1024);
    if (!ptr)
        perror("minishell : pwd error :");
    else
      printf("%s\n", ptr);
      if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    return (1);
}

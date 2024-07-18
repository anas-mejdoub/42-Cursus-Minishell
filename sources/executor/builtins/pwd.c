/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:46:05 by nbenyahy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/11 17:18:42 by amejdoub         ###   ########.fr       */
=======
/*   Updated: 2024/07/11 19:11:37 by nbenyahy         ###   ########.fr       */
>>>>>>> 18f3ba1c5dff56df25e85c27efb21cca3f6b88a4
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

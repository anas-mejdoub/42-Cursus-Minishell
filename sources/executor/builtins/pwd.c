/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:46:05 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 17:33:41 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int	pwd_cmd(t_command *cmd)
{
	char	tmp[1024];
	char	*ptr;
	int		fd_in;
	int		fd_out;

	if (cmd->args && !(!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))
			&& ft_strlen(cmd->args[0]) == ft_strlen("pwd")))
		return (-1);
	if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	ptr = getcwd(tmp, 1024);
	if (!ptr)
		print_err(2, 1, "minishell : pwd error :", strerror(errno));
	else
		printf("%s\n", ptr);
	if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	return (1);
}

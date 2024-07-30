/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 09:58:21 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/30 11:12:29 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

static int	check_argument(t_command *cmd, int *new_line)
{
	int		i;
	char	*str;

	i = 1;
	while (cmd->args && cmd->args[i] && cmd->args[i][0]
		&& cmd->args[i][0] == '-')
	{
		if (cmd->args && cmd->args[i] && cmd->args[i][0] == '-'
			&& cmd->args[i][1])
		{
			str = ft_strtrim(cmd->args[i] + 1, "n");
			if (str[0] == '\0')
			{
				*new_line = 0;
				i++;
			}
			else
				break ;
		}
		else if (!cmd->args[i][1])
			break ;
	}
	return (i);
}

static void	print_content(t_command *cmd)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = check_argument(cmd, &new_line);
	while (cmd->args && cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
}

int	echo_cmd(t_command *cmd)
{
	int	fd_in;
	int	fd_out;

	if (cmd->args && !(!ft_strncmp(cmd->args[0], "echo",
				ft_strlen(cmd->args[0]))
			&& ft_strlen(cmd->args[0]) == ft_strlen("echo")))
		return (-1);
	if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	print_content(cmd);
	if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	return (0);
}

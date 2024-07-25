/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:09:14 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/25 07:42:14 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

static int	overflow_result(int nbr)
{
	if (nbr > 255)
		return (nbr % 256);
	else if (nbr < 0)
		return ((nbr % 256) + 256);
	return (nbr);
}

static int	extract_number(t_command *cmd, int *fd_in, int *fd_out)
{
	unsigned long long	res;
	int					sign;
	int					j;

	j = 0;
	res = 0;
	sign = 1;
	while (cmd->args[1][j] == ' ' || (cmd->args[1][j] >= 9
			&& cmd->args[1][j] <= 13))
		j++;
	if (cmd->args[1][j] == '-' || cmd->args[1][j] == '+')
	{
		if (cmd->args[1][j++] == '-')
			sign = -1;
	}
	while (cmd->args[1][j] && ft_isdigit(cmd->args[1][j]))
	{
		res = (res * 10) + (cmd->args[1][j++] - '0');
		if ((res > LLONG_MAX && sign == 1) || (res > LLONG_MAX && sign == -1))
			return (restor_rediraction(cmd, fd_in, fd_out), print_err(4, 255,
					"minishell: exit: ", cmd->args[1],
					": numeric argument required\n"), free_tree(cmd), exit(255),
				-1);
	}
	return (overflow_result(res * sign));
}

static int	calculate_status(t_command *cmd, int *fd_in, int *fd_out)
{
	int	exit_status;
	int	j;

	j = 0;
	if (cmd->args[1][0] == '-' || cmd->args[1][0] == '+')
		j++;
	while (cmd->args[1][j] && ft_isdigit(cmd->args[1][j]))
		j++;
	if (cmd->args[1][j] || !ft_isdigit(cmd->args[1][j - 1]))
		return (print_err(4, 255, "minishell: exit: ", cmd->args[1],
				": numeric argument required\n"), restor_rediraction(cmd, fd_in,
				fd_out), free_tree(cmd), exit(255), -1);
	else
	{
		if (cmd->args[1] != NULL && cmd->args[2] != NULL)
			return (print_err(2, 1, "minishell: exit: too many arguments\n"),
				restor_rediraction(cmd, fd_in, fd_out), -1);
		else
			exit_status = extract_number(cmd, fd_in, fd_out);
		restor_rediraction(cmd, fd_in, fd_out);
		free_tree(cmd);
		exit(exit_status);
	}
	return (0);
}

int	exit_comand(t_command *cmd)
{
	int	fd_in;
	int	fd_out;

	if (cmd->args && !(!ft_strncmp(cmd->args[0], "exit",
				ft_strlen(cmd->args[0]))
			&& ft_strlen(cmd->args[0]) == ft_strlen("exit")))
		return (-1);
	if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	if (cmd->args[1] == NULL)
	{
		restor_rediraction(cmd, &fd_in, &fd_out);
		free_tree(cmd);
		exit(globalVar);
	}
	return (restor_rediraction(cmd, &fd_in, &fd_out), calculate_status(cmd,
			&fd_in, &fd_out));
}

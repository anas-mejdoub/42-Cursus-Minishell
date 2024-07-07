/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:09:14 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/07 13:14:49 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int	exit_comand(t_command *cmd)
{
	int a;
	int exit_status;

	if (cmd->args && !(!ft_strncmp(cmd->args[0], "exit",
				ft_strlen(cmd->args[0]))
			&& ft_strlen(cmd->args[0]) == ft_strlen("exit")))
		return (-1);
	int i = 1;
	while (cmd->args[i])
	{
		int j = 0;
		if (cmd->args[i][0] == '-' || cmd->args[i][0] == '+')
			j++;
		while (cmd->args[i][j] && ft_isdigit(cmd->args[i][j]))
			j++;
		if (cmd->args[i][j])
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", cmd->args[i]);
			exit(255);
		}
		else
		{
			unsigned long long res;
            long long exit_status;
			int sign;
            int j;

            j = 0;
			res = 0;
			sign = 1;
			while (cmd->args[1][j] == ' ' || (cmd->args[1][j] >= 9 && cmd->args[1][j] <= 13))
				j++;
			if (cmd->args[1][j] == '-' || cmd->args[1][j] == '+')
			{
				if (cmd->args[1][j] == '-')
					sign = -1;
				j++;
			}
			while (cmd->args[1][j] && ft_isdigit(cmd->args[1][j]))
			{
				res = (res * 10) + (cmd->args[1][j] - '0');
				if ((res > LLONG_MAX && sign == 1) || (res * sign < LLONG_MIN))
                {
			        printf("exit\n");
					printf("minishell: exit: %s: numeric argument required\n", cmd->args[i]);
                    exit(255);
                }
				j++;
			}
            printf("exit\n");
            exit(exit_status);
			// return (res * sign);
		}
	}
}
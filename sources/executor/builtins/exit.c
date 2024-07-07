/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:09:14 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/07 19:38:34 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int	exit_comand(t_command *cmd)
{
    long long tmp_int;
    long long exit_status;
	unsigned long long res;
	int sign;


	if (cmd->args && !(!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("exit")))
		return (-1);
    if (cmd->args[1] == NULL)
    {
        printf("exit\n");
        free_tree(cmd);
        exit(0);
    }
    if (cmd->args[1] != NULL && cmd->args[2] != NULL)
    {
        printf("exit\nminishell: exit: too many arguments\n");
        return (1);
    }
		int j = 0;
		if (cmd->args[1][0] == '-' || cmd->args[1][0] == '+')
			j++;
		while (cmd->args[1][j] && ft_isdigit(cmd->args[1][j]))
			j++;
		if (cmd->args[1][j])
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n", cmd->args[1]);
            free_tree(cmd);
			exit(255);
		}
		else
		{
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
				if ((res > LLONG_MAX && sign == 1) || (res > LLONG_MAX && sign == -1))
                {
			        printf("exit\n");
					printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
                    free_tree(cmd);
                    exit(255);
                }
				j++;
			}
            exit_status = res * sign;
            while(exit_status < 0)
            {
                tmp_int = exit_status + 256;
                exit_status = tmp_int;
            }
            while(exit_status > 255)
            {
                tmp_int = exit_status - 256;
                exit_status = tmp_int;
            }
            free_tree(cmd);
            exit(exit_status);
		}
    return (0);
}

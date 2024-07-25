/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:00:58 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 18:38:54 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

static void	print_err_and_change_status(char *str, int *status)
{
	print_err(4, 1, "minishell: unset: `", str, "': not a valid identifier\n");
	*status = -1;
}

static void	unset_vars(t_command *cmd, t_env *env, int *status)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->args[i])
	{
		j = 0;
		if (ft_isalpha(cmd->args[i][j]) || cmd->args[i][j] == '_')
		{
			while (cmd->args[i][j] && (ft_isalnum(cmd->args[i][j])
					|| cmd->args[i][j] == '_'))
				j++;
			if (cmd->args[i][j])
				print_err_and_change_status(cmd->args[i], status);
			else
				env->unset(&env->data, cmd->args[i]);
		}
		else
			print_err_and_change_status(cmd->args[i], status);
		i++;
	}
}

int	unset_cmd(t_command *cmd, t_env *env)
{
	int	fd_in;
	int	fd_out;
	int	status;

	status = 0;
	if (!env || !env->data)
		return (0);
	if (cmd->args && !(!ft_strncmp(cmd->args[0], "unset",
				ft_strlen(cmd->args[0]))
			&& ft_strlen(cmd->args[0]) == ft_strlen("unset")))
		return (-1);
	if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	unset_vars(cmd, env, &status);
	if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
		return (-1);
	return (status);
}

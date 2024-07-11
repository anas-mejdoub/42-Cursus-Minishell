/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:00:58 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/11 16:22:39 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int unset_cmd(t_command *cmd, t_env *env)
{
    int i ;
        int fd_in;
    int fd_out;

    if (!env || !env->data)
        return (0);
    if (cmd->args && !(!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("unset")))
		return (-1);
    if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    i = 1;
    while (cmd->args[i])
    {
        int j = 0;
        if (ft_isalpha(cmd->args[i][j]) || cmd->args[i][j] == '_')
        {
            while (cmd->args[i][j] && (ft_isalnum(cmd->args[i][j]) || cmd->args[i][j] == '_'))
                j++;
            if (cmd->args[i][j])
            {
                printf("minishell: unset: `%s': not a valid identifier\n", cmd->args[i]);
                return (restor_rediraction(cmd, &fd_in, &fd_out), -1);
            }
            else
                env->unset(&env->data, cmd->args[i]);
        }
        else
            printf("minishell: unset: `%s': not a valid identifier\n", cmd->args[i]);

        i++;
    }
    if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    return (0);
}
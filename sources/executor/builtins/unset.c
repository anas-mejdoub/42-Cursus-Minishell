/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:00:58 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/07 17:37:07 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int unset_cmd(t_command *cmd, t_env *env)
{
    int i ;

    if (cmd->args && !(!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("unset")))
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
                return (-1);
            }
            else
                env->unset(env->data, cmd->args[i]);
        }
        i++;
    }
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:15:58 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/07 11:00:27 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int env_cmd(t_command *cmd, t_env *env)
{
    t_env_data *tmp;

    tmp = env->data;
    if (cmd->args && !(!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("env")))
        return (-1);
    if (cmd->args[1])
        return (printf("minishell: `%s': env command with no arg or opt\n", cmd->args[1]), -1);
    while (tmp)
    {
        if (tmp->value)
            printf("%s=%s\n", tmp->key, tmp->value);
        tmp= tmp->next;
    }
    return (0);
}
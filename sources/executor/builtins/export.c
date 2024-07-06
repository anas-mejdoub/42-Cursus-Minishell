/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:35:02 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/06 15:40:59 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"


int export_cmd(t_command *cmd, t_env *env)
{
    int i;
    
    if (cmd->args && !(!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("export")))
        return (-1);
    i = 1;
    
    while (cmd->args[i])
    {
        int j = 0;
        if (ft_isalpha(cmd->args[i][j]) || cmd->args[i][j] == '_')
        {
            while (cmd->args[i][j] && (ft_isalnum(cmd->args[i][j]) || cmd->args[i][j] == '_'))
                j++;
            if (cmd->args[i][j] == '\0')
            {
                i++;
                continue;
            }
            if (cmd->args[i][j] != '=')
            {
                printf("minishell: export: `%s': not a valid identifier\n", cmd->args[i]);
                continue;
            }
            else if (cmd->args[i][j] == '=')
            {
                int len = j;
                char *key = ft_substr(cmd->args[i], 0, len);
                char *value = ft_substr(cmd->args[i] + len + 1, 0, ft_strlen(cmd->args[i] + len + 1));
                env->set(&env->data, key, value);
            }
        }
        else
            printf("minishell: export: `%s': not a valid identifier\n", cmd->args[i]);
        i++;
    }
    return (0);
}
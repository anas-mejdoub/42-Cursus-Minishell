/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:35:02 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/08 12:27:41 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"


int export_cmd(t_command *cmd, t_env *env)
{
    int i;
    t_env_data *tmp_env_data;
    if (!env)
        return (0);
    if (cmd->args && !(!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("export")))
        return (-1);
    i = 1;
    char *key;
    while (cmd->args[i])
    {
        int j = 0;
        if (ft_isalpha(cmd->args[i][j]) || cmd->args[i][j] == '_')
        {
            while (cmd->args[i][j] && (ft_isalnum(cmd->args[i][j]) || cmd->args[i][j] == '_'))
                j++;
            if (cmd->args[i][j] == '\0')
            {
                int len = j;
                key = ft_substr(cmd->args[i], 0, len);
                env->set(&env->data, key, NULL);
                i++;
                continue;
            }
            if (cmd->args[i][j] != '=')
            {
                printf("minishell: export: `%s': not a valid identifier\n", cmd->args[i]);
                i++;
                continue;
            }
            else if (cmd->args[i][j] == '=')
            {
                int len = j;
                key = ft_substr(cmd->args[i], 0, len);
                char *value = ft_substr(cmd->args[i] + len + 1, 0, ft_strlen(cmd->args[i] + len + 1));
                env->set(&env->data, key, value);
            }
        }
        else
        {
            printf("minishell: export: `%s': not a valid identifier\n", cmd->args[i]);
            return (-1);
        }
        i++;
    }
    if (i == 1)
    {
        tmp_env_data = env->data;
        while (tmp_env_data)
        {
            printf("declare -x %s", tmp_env_data->key);
            if (tmp_env_data->value)
                printf("=%s", tmp_env_data->value);
            printf("\n");
            tmp_env_data = tmp_env_data->next;
        }
    }
    return (0);
}
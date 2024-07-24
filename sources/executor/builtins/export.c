/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:35:02 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/24 17:31:29 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"


int export_cmd(t_command *cmd, t_env *env)
{
    int ret = 0;
    int i;
        int fd_in;
    int fd_out;
    t_env_data *tmp_env_data;
    if (!env)
        return (0);
    if (cmd->args && !(!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("export")))
        return (-1);
    if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
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
                ft_putstr_fd("minishell: export: `", 2);
			    ft_putstr_fd(cmd->args[i], 2);
			    ft_putstr_fd("': not a valid identifier\n", 2);
                ret = -1;
                globalVar = 1;
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
            ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
            ret = -1;
            globalVar = 1;
            i++;
            continue;
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
            {
                printf("=\"");
                int k = 0;
                while (tmp_env_data->value[k])
                {
                    if (tmp_env_data->value[k] == '\"' || tmp_env_data->value[k] == '$')
                        printf("\\");
                    printf("%c", tmp_env_data->value[k]);
                    k++;
                }
                printf("\"");
            }
            printf("\n");
            tmp_env_data = tmp_env_data->next;
        }
    }
    if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    return (ret);
}

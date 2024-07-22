/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:15:58 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/22 15:51:03 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int env_cmd(t_command *cmd, t_env *env)
{
    t_env_data *tmp;
        int fd_in;
    int fd_out;

    if (!env)
        return (0);
    tmp = env->data;
    if (cmd->args && !(!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("env")))
        return (-1);
    if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    if (cmd->args[1])
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->args[1], 2);
        ft_putstr_fd(": env command with no arg or opt\n", 2);
        return (-1);
    }
        // return (restor_rediraction(cmd, &fd_in, &fd_out), printf("minishell: `%s': env command with no arg or opt\n", cmd->args[1]), -1);
    while (tmp)
    {
        if (tmp->value)
            printf("%s=%s\n", tmp->key, tmp->value);
        tmp= tmp->next;
    }
    if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:33:22 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/07 19:40:28 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

char *working_dir(void)
{
    char tmp[1024];
    char *ptr;

    ptr = getcwd(tmp, 1024);
    if (!ptr)
        perror("minishell :");
    return (ptr);
}

int cd_cmd(t_command *cmd, t_env *env)
{
    char *path;
    char *pwd;
    char *oldpwd;

    if (cmd->args && !(!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("cd")))
		return (-1);
    oldpwd = working_dir();
    pwd = env->get(env->data, "PWD");
    if (cmd->args[1] == NULL)
        path = env->get(env->data, "HOME");
    else
        path = cmd->args[1];
    if (!path && cmd->args[1] == NULL)
    {
        printf("minishell: cd: HOME not set");
        return (-1);
    }

    if(chdir(path) == -1)
    {
        perror("minishell ");
        return (-1);
    }
    if (env->get(env->data, "OLDPWD"))
        env->set(&env->data, "OLDPWD", oldpwd);
    if (env->get(env->data, "PWD"))
        env->set(&env->data, "PWD", working_dir());
    return (0);
}
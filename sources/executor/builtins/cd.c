/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:33:22 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/11 15:28:11 by nbenyahy         ###   ########.fr       */
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
        int fd_in;
    int fd_out;
    
    if (!env)
        return (0);
    if (cmd->args && !(!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) && ft_strlen(cmd->args[0]) == ft_strlen("cd")))
		return (-1);
    if (change_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    oldpwd = working_dir();
    
    pwd = env->get(env->data, "PWD");
    if (cmd->args[1] == NULL)
        path = env->get(env->data, "HOME");
    else
        path = cmd->args[1];
    if (!path && cmd->args[1] == NULL)
    {
        ft_putendl_fd("minishell: cd: HOME not set", 2);
        // printf("minishell: cd: HOME not set\n");
        return (restor_rediraction(cmd, &fd_in, &fd_out), -1);
    }

    if(chdir(path) == -1)
    {
        perror("minishell ");
        return (restor_rediraction(cmd, &fd_in, &fd_out), -1);
    }
    if (env->get(env->data, "OLDPWD"))
        env->set(&env->data, "OLDPWD", oldpwd);
    if (env->get(env->data, "PWD"))
        env->set(&env->data, "PWD", working_dir());
    if (restor_rediraction(cmd, &fd_in, &fd_out) == -1)
        return (-1);
    return (0);
}
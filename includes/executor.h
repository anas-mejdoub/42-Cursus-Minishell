/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:06 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/24 12:28:46 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
#include "minishell.h"
#include "env.h"
#include "parser.h"
typedef struct s_exec_ret
{
    int ret;
    int *pids;
} t_exec_ret;
t_exec_ret *executor(t_command *commands, t_env *env, char c, char **ev);
typedef struct s_env_d
{
    char **ev;
    t_env *env;
} t_env_d;
#endif
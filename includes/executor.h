/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:06 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/06 12:53:11 by nbenyahy         ###   ########.fr       */
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
t_exec_ret *executor(t_command *commands, t_env *env, char c);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:26:21 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/06 15:27:39 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// int echo(t_command *cmd);
int pwd(void);
void env_command(t_env *env);
int echo_cmd(t_command *cmd);
int export_cmd(t_command *cmd, t_env *env);

#endif
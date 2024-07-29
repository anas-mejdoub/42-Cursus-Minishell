/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:26:21 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 09:21:14 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	pwd_cmd(t_command *cmd);
int	exit_comand(t_command *cmd);
int	env_cmd(t_command *cmd, t_env *env);
int	echo_cmd(t_command *cmd);
int	export_cmd(t_command *cmd, t_env *env);
int	cd_cmd(t_command *cmd, t_env *env);
int	unset_cmd(t_command *cmd, t_env *env);

#endif
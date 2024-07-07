/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:40:27 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/07 11:32:01 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include "minishell.h"
char    *env_expander(char *content, t_env_index *index, t_env *env);
int     open_out_files(t_out_files *files, t_env *env);
int     open_in_files(t_in_files *files, t_env *env);
void free_tree(t_command *cmd);
int do_builtin(t_command *cmd, t_env *env);
int is_builtin(t_command *cmd);
// int     open_out_files(t_out_files *files, t_env *env);

#endif
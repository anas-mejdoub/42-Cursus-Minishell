/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:40:27 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/26 10:18:25 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include "minishell.h"
char	*env_expander(char *content, t_env_index *index, t_env *env,
			bool wild_card);
int		open_out_files(t_out_files *files, t_env *env);
int		open_in_files(t_in_files *files, t_env *env);
void	free_tree(t_command *cmd);
int		do_builtin(t_command *cmd, t_env *env);
int		is_builtin(t_command *cmd);
char	**env_to_2d_arr(t_env *env);
int		change_rediraction(t_command *cmd, int *fd_in, int *fd_out);
int		restor_rediraction(t_command *cmd, int *fd_in, int *fd_out);
void	print_err(int count, ...);
bool	env_pattern(char a);
bool	is_redirection(char c);
bool	is_spliter(char c);
bool	is_red_spliter(char c);
bool	is_qoutes(char c);
bool	in_qoutes(char c);
char	*ft_freed_join(char *s1, char *s2);
// int     open_out_files(t_out_files *files, t_env *env);

#endif
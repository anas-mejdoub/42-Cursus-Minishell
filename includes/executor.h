/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:06 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 12:09:51 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "env.h"
# include "minishell.h"
# include "parser.h"

typedef struct s_exec_ret
{
	int		ret;
	int		*pids;
}			t_exec_ret;

t_exec_ret	*executor(t_command *commands, t_env *env, char c);
// typedef struct s_env_d
// {
// 	char	**ev;
// 	t_env	*env;
// }			t_env;
void		v_close_fd(int n, ...);
void		print_err_exit(int count, ...);
void		close_fds(int *arr);
char		*fetch_paths(char **paths, char *command);
char		*get_path(char *command, t_env *env);
char		**commands_args_helper(char *tmp_str, t_command_args *args,
				char **res);
char		**get_command_args(t_command_args *args, t_env *env);
void		share_fds(t_command *command);
bool		get_files(t_command *command, t_env *env, bool *found_in);
t_exec_ret	*cmd_node(t_command *command, t_exec_ret *ret, t_env *env, char c);
void		handle_intr_sig(int sig);
t_exec_ret	*and_node(t_command *command, t_exec_ret *ret, t_env *env);
t_exec_ret	*or_node(t_command *command, t_exec_ret *ret, t_env *env);
bool		pipeline_node(t_command **command, t_exec_ret *ret, t_env *env);
bool		if_pipeline(t_command **command, int fd[2]);
void		subshell_childp(t_command *command, t_exec_ret *ret, t_env *env,
				char c);
void		subshell_parentp(t_command *command, t_exec_ret *ret, int f,
				char c);
t_exec_ret	*subshell_node(t_command *command, t_exec_ret *ret, t_env *env,
				char c);
void		child_proc(t_command *command, char c, bool f, t_env *env);
void		parent_proc(t_command *command, t_exec_ret *ret, char c, int i);
bool		second_cmd(t_command *cmd, t_exec_ret *ret, t_env *env);
void		duping(t_command *command);
void		right_left(t_command *command, char c);
void		waiting_pids(t_exec_ret *ret);
void		wait_one(t_exec_ret *ret);
bool		get_files_args(t_command *command, t_env *env, bool *found_in);
t_exec_ret	*single_built(t_command *cmd, t_exec_ret *ret, bool f, t_env *env);
bool		args_help(t_command_args **a, char *tmp_str);

#endif
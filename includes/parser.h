/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:01:25 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/30 12:02:29 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define STR "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
# include "env.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_bool_param
{
	bool					bool1;
	bool					bool2;
}							t_bool_param;

enum						e_type_node
{
	NODE = 1,
	PIPE_LINE_NODE = 2,
	AND_NODE = 3,
	OR_NODE = 4,
	ROOT_NODE,
	SUBSHELL_NODE,
};

enum						e_node_rank
{
	P = 1,
	A = 2,
	O = 2,
};

typedef struct s_env_index
{
	int						index;
	int						len;
	bool					expanded;
	struct s_env_index		*next;
}							t_env_index;

typedef struct s_out_files
{
	char					*filename;
	bool					append;
	bool					ambiguous;
	t_env_index				*index_list;
	bool					wildcard;
	struct s_out_files		*next;
}							t_out_files;
typedef struct s_command_h_ret
{
	char					*command;
	int						index;
	bool					wildcard;
	int						*arr;
	int						*lens;
	bool					including_null;
	bool					env;
}							t_command_h_ret;
typedef struct s_in_files
{
	char					*filename;
	bool					here_doc;
	bool					ambiguous;
	char					*limiter;
	t_env_index				*index_list;
	bool					wildcard;
	struct s_in_files		*next;
}							t_in_files;

typedef struct s_command_args
{
	char					*content;
	t_env_index				*index_list;
	bool					wildcard;
	bool					including_null;
	bool					env;
	struct s_command_args	*next;
}							t_command_args;

typedef struct s_commands
{
	int						fd[2];
	int						*to_close;
	t_command_args			*command_arg;
	char					**args;
	int						type_node;
	char					**infile;
	char					**outfile;
	t_out_files				*outfiles;
	t_in_files				*in_files;
	char					*path;
	bool					dup;
	bool					pipe;
	int						infd;
	int						outfd;
	bool					and_;
	bool					or_;
	bool					builtin;
	bool					in_redir;
	bool					out_redir;
	bool					dredir;
	bool					here_doc;
	void					*right;
	void					*left;
}							t_command;

t_command					*parser(t_elem *elements, t_env *env);
void						print_tree(t_command *root, int n);
void						free2d(char **str);
char						**add_to_args(char **args, char *to_append);
int							*add_int(int *arr, int new);
char						*random_str(void);
bool						redir_in_parse(t_elem **elements,
								t_command **command, t_env *env);
void						redir_out_parse(t_elem **elements,
								t_command **command, t_env *env);
void						handle_redir_out(t_command *command, char *filename,
								bool ambiguous, bool wild_card);
int							handle_redir_in(t_command *command, char *filename,
								t_bool_param bool_param, t_env *env);

t_in_files					*new_in_file(char *filename, bool here_doc,
								bool env_qoute, bool wild_card);
t_in_files					*get_last_in_file(t_in_files *files);
bool						parser_redirs_switch(t_elem **elem, t_command **cmd,
								t_env *env);
void						command_args_parse(t_elem **elements,
								t_command **command);
t_command_args				*get_last_arg(t_command_args *command);
void						add_to_command(t_command *command,
								t_command_args *new_arg);
t_command_args				*new_arg(char *content, bool including_null,
								bool wild_card, bool env);
t_command_h_ret				*command_handling(t_elem **element);
void						command_handl_core(t_elem **element,
								t_command_h_ret *res);

void						handle_quotes_case(t_elem **element,
								t_command_h_ret *res);
void						handle_empty_quote(t_command_h_ret *res);
t_env_index					*new_index(int new, int len);
t_env_index					*last_index(t_env_index *list);
void						add_to_index(t_command_args *list,
								t_env_index *new);
int							env_index(char *env_str, char *prev);
char						**add_to_args(char **args, char *to_append);
bool						redir_out_condition(t_elem *elements,
								t_command *command);
bool						redir_in_condition(t_elem *elements,
								t_command *command);
bool						args_parse_condit(t_elem *elements,
								t_command *command);
bool						command_args_condition(t_elem *elements,
								t_command *command);
bool						subshell_container(t_elem **elem, t_command **cmd,
								t_env *env);
int							add_to_infiles(t_command *command, t_in_files *file,
								t_env *env);
int							set_type_node(int type_elem);
t_command					*handle_pipe_node(t_command *command,
								int type_elem);
t_command					*new_node(void);
void						intialize_new_node(t_command *new);
int							allocate_node1(t_elem **elem, char *content,
								int state, int token);
void						add_indexs_to_infiles(int *arr, int *len,
								t_in_files *file);
void						add_to_in_index(t_in_files *list, t_env_index *new);
t_out_files					*new_file(char *filename, bool append,
								bool ambiguous, bool wild_card);
t_out_files					*get_last_file(t_out_files *files);
void						add_to_outfiles(t_command *command,
								t_out_files *file);
void						add_indexs_to_args(int *arr, int *lens,
								t_command_args *args);
bool						split_tree_cond(t_elem *elements, bool ft);
void						intialize_parser(t_command **command,
								t_command **pipe_node, bool *f, int *r);
void						add_to_out_index(t_out_files *list,
								t_env_index *new);
void						add_indexs_to_outfiles(int *arr, int *len,
								t_out_files *file);
int							split_tree(t_elem **elements, t_command **command,
								t_command **pipe_node, int *r);
bool						f_split_tree_cond(t_elem *elements, bool ft);
char						*random_str(void);
int							my_rand(void);
int							*add_int(int *arr, int new);
int							handle_here_doc(t_in_files *file, t_env *env);
void						handle_general_case(t_elem **element,
								t_command_h_ret *res);
void						handle_env_case(t_elem **element,
								t_command_h_ret *res);
int							get_rank(int n);
char						*wild_card_handler(t_command_h_ret *res);
int							first_split_tree(t_elem *elements,
								t_command **command, t_command **pipe_node,
								bool *f);
t_command_h_ret				*intialize_ret_cmd(void);
bool						mini_condition(char *command);
#endif
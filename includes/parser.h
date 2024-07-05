/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:01:25 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/05 16:09:31 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H
#include <stdbool.h>
# include <fcntl.h>
#include "minishell.h"
#include "env.h"

enum e_type_node
{
    NODE = 1,
    PIPE_LINE_NODE = 2,
    AND_NODE = 3,
    OR_NODE = 4,
    ROOT_NODE,
};



typedef struct s_env_index
{
    int index;
    int len;
    bool expanded;
    struct s_env_index *next;
} t_env_index;
typedef struct s_out_files
{
    char *filename;
    bool append;
    bool in_qoute;
    t_env_index *index_list;
    struct s_out_files *next;
} t_out_files;
typedef struct s_command_h_ret
{
    char *command;
    int index;
    int *arr;
    int *lens;
    bool env;
} t_command_h_ret;
typedef struct s_in_files
{
    char *filename;
    bool here_doc;
    bool in_qoute;
    char *limiter;
    t_env_index *index_list;
    struct s_in_files *next;
} t_in_files;

typedef struct s_command_args
{
    char *content;
    t_env_index *index_list;
    bool env;
    struct s_command_args *next;
}t_command_args;

typedef struct s_commands
{
    t_command_args *command_arg;
    char **args;
    int type_node;
    char  **infile;
    char **outfile;
    t_out_files *outfiles;
    t_in_files *in_files;
    char *path;
    bool pipe;
    int infd;
    int outfd;
    bool and_;
    bool or_;
    bool builtin;
    bool in_redir;
    bool out_redir;
    bool dredir;
    bool here_doc;
    void *right;
    void *left;
} t_command;

t_command	*parser(t_elem *elements);
void print_tree(t_command *root, int n);
void	free2d(char **str);
char	**add_to_args(char **args, char *to_append);
int *add_int(int *arr, int new);
#endif
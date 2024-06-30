/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:01:25 by amejdoub          #+#    #+#             */
/*   Updated: 2024/06/30 14:51:52 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H
#include <stdbool.h>
# include <fcntl.h>

enum e_type_node
{
    NODE = 1,
    PIPE_LINE_NODE = 2,
    AND_NODE = 3,
    OR_NODE = 4,
};


typedef struct s_out_files
{
    char *filename;
    bool append;
    struct s_out_files *next;
} t_out_files;

typedef struct s_command_h_ret
{
    char *command;
    bool env;
} t_command_h_ret;
typedef struct s_in_files
{
    char *filename;
    bool here_doc;
    char *limiter;
    struct s_in_files *next;
} t_in_files;

typedef struct s_command_args
{
    char *content;
    bool env;
    struct s_command_args *next;
}t_command_args;

typedef struct s_commands
{
    char **command_args;
    t_command_args *command_arg;
    int type_node;
    char  **infile;
    char **outfile;
    t_out_files *outfiles;
    t_in_files *in_files;
    char *path;
    bool pipe;
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

#endif
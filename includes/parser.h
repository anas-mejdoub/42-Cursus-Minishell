/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:01:25 by amejdoub          #+#    #+#             */
/*   Updated: 2024/06/20 12:57:06 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H
#include <stdbool.h>


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

typedef struct s_commands
{
    char **command_args;
    int type_node;
    char  **infile;
    char **outfile;
    t_out_files *outfiles;
    char *path;
    bool pipe;
    bool and_;
    bool or_;
    bool builtin;
    bool in_redir;
    bool out_redir;
    bool dredir;
    void *right;
    void *left;
} t_command;

t_command	*parser(t_elem *elements);
void print_tree(t_command *root, int n);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:01:25 by amejdoub          #+#    #+#             */
/*   Updated: 2024/06/21 16:59:07 by nbenyahy         ###   ########.fr       */
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

typedef struct s_commands
{
    char **command_args;
    int type_node;
    char  **infile;
    char **outfile;
    char *path;
    bool pipe;
    bool and_;
    bool or_;
    bool builtin;
    bool in_redir;
    bool out_redir;
    void *right;
    void *left;
} t_command;

t_command	*parser(t_elem *elements);
void print_tree(t_command *root, int n);

#endif
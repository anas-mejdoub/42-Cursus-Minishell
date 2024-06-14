/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:01:25 by amejdoub          #+#    #+#             */
/*   Updated: 2024/06/14 19:25:59 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H
#include <stdbool.h>


enum e_type_node
{
    NODE = 1,
    PIPE_LINE_NODE = 2,
};

typedef struct s_commands
{
    char **command_args;
    int type_node;
    char  *infile;
    char *outfile;
    char *path;
    bool pipe;
    bool and_;
    bool or_;
    bool builtin;
    struct s_command* left;
    struct s_command* right;
} t_command;


#endif
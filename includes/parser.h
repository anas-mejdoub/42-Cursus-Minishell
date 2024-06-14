/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:01:25 by amejdoub          #+#    #+#             */
/*   Updated: 2024/06/14 16:08:55 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H


enum e_type_node
{
    NODE = 1,
    PIPE_LINE = 2,
};

typedef struct commands
{
    char **command_args;
    int type_node;
    int infile;
    int outfile;
    char *path;
    bool pipe;
    bool and_;
    bool or_;
    bool builtin;
    struct command* left;
    struct command* right;
} command_t;


#endif
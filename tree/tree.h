#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tree
{
    /* data */
    char *command;
    struct tree* left;
    struct tree* right;
} t_tree;

#endif
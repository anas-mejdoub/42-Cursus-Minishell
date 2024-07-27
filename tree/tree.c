#include "tree.h"



t_tree *new_node(char *command)
{
    t_tree *new = malloc (sizeof(t_tree));
    new->command = command;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void add_to_right(t_tree *tree, t_tree *right)
{
    tree->right = right;
}
void add_to_left(t_tree *tree, t_tree *left)
{
    tree->left = left;
}

void print_tree(t_tree *tree)
{
    if (!tree)
        return;
    printf("%s\n", tree->command);
    print_tree(tree->right);
    print_tree(tree->left);
}


int main()
{
    t_tree *tree;
    tree = malloc (sizeof(t_tree));
    tree->command = strdup("ls");
    tree->left = NULL;
    tree->right = NULL;
    add_to_right(tree, new_node(strdup("wc -l")));
    add_to_right(tree->right, new_node(strdup("m the right of the right node of the root")));
    add_to_left(tree, new_node(strdup("echo hello")));
    print_tree(tree);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:16:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/04 10:38:47 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tchbi7a(void)
{
    printf(RED "██████  ██░ ██ ▓█████  ██▓     ██▓            \n"
"▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒            \n"
"░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░            \n"
"  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░            \n"
"▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒        \n"
"▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░        \n"
"░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░        \n"
"░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░           \n"
"      ░   ░  ░  ░   ░  ░    ░  ░    ░  ░        \n" RESET);
}

int main(int ac, char **av, char  **ev)
{
    t_env *env;
    (void)ac;
    (void)av;
    
    // (void)ev;
    print_tchbi7a();
    env = init_env(ev);
    // printf("%s\n", env->get(env->data, "HOME"));
    t_elem *elem;
    // env_command(env);
    while (1)
    {
        elem = lexer();
        if (!elem)
            continue;
        t_command *root = parser(elem);
        // printf("%s\n", env_expander((((t_command *)root->right))->command_arg->content, (((t_command *)root->right))->command_arg->index_list, env));
        print_tree(root, 0);
        while (elem)
        {
            printf("~%s~                       ", elem->content);
            printf("~%c~                       ", elem->type == WORD ? 'W' : elem->type == AND ? 'A' : elem->type == OR ? 'O' : elem->type == HERE_DOC ? 'H' : elem->type == DREDIR_OUT ? 'D' : elem->type);
            printf("~%s~        \n", elem->state == GENERAL ? "GENERAL" : elem->state == IN_DQUOTE ? "IN DOUBLE QUOTE" : "IN QOUTE");
            elem = elem->next;
        }
    //     // char *content  = here_doc("$lim");
    //     // // printf("here doc content without expanding");
    //     // if (content)
    //     //     printf("here doc content with expanding : %s\n", expand_here_doc_content(content, env));
    }
}
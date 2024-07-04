/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:16:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/04 11:36:05 by amejdoub         ###   ########.fr       */
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
    // env_handeler_test("hello $HOME $?fasdf$_vdfv1", env);
    while (1)
    {
        elem = lexer();
        if (!elem)
            continue;
        // t_env *env;
        t_command *root = parser(elem);
        // int *arr = NULL;
        t_exec_ret *r =  executor(root, env, '\0');
        
        int i = 0;
        if (!r || !r->pids)
            printf("problem with the r\n");
        while (r && r->pids && r->pids[i])
        {
            // printf("wait the id : %d\n", r->pids[i]);
            if (r->pids[i] == -1)
                break;
            waitpid(r->pids[i], NULL, 0);
            i++;
        }
        // while (1)
        // {
        //     i = executor(root, env, '\0');
        //     waitpid(i, NULL, 0);
        //     printf("after wait\n");
        //     if (i == -1)
        //     {
        //         printf("it the end of the prompt !\n");
        //         break;
        //     }
        // }
        // print_tree(root, 0);
        // while (elem)
        // {
        //     printf("~%s~                       ", elem->content);
        //     printf("~%c~                       ", elem->type == WORD ? 'W' : elem->type == AND ? 'A' : elem->type == OR ? 'O' : elem->type == HERE_DOC ? 'H' : elem->type == DREDIR_OUT ? 'D' : elem->type);
        //     printf("~%s~        \n", elem->state == GENERAL ? "GENERAL" : elem->state == IN_DQUOTE ? "IN DOUBLE QUOTE" : "IN QOUTE");
        //     elem = elem->next;
        // }
    //     // char *content  = here_doc("$lim");
    //     // // printf("here doc content without expanding");
    //     // if (content)
    //     //     printf("here doc content with expanding : %s\n", expand_here_doc_content(content, env));
    }
}
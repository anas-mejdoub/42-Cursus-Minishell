/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:59:33 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/07 19:31:41 by amejdoub         ###   ########.fr       */
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
// int globalVar;
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
        t_command *root = parser(elem, env);

        t_exec_ret *r =  executor(root, env, '\0', ev);
        // echo(root->right);

        // print_tree(root, 0);
        // int *arr = NULL;
        // t_exec_ret *r =  executor(root, env, '\0');
        
        int i = 0;
        int hehe= 0;
        if (!r || !r->pids)
            printf("problem with the r\n");
        while (r && r->pids)
        {
            if (r->pids[i] == -1)
                break;
            waitpid(r->pids[i], &hehe, 0);
            if (WIFEXITED(hehe))
                globalVar = WEXITSTATUS(hehe);
            else if (WIFSIGNALED(hehe))
                globalVar = WTERMSIG(hehe) + 128;
            i++;
        }
        // globalVar = 28 << 8;
        // printf("exit : %d\n", globalVar);
        // printf("hehe : %d\n", WEXIT(hehe));
        free_tree(root);
        // while (1);
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
        // open_out_files(((t_command *)(root->right))->outfiles, env);
        // print_tree(root, 0);
        // open_out_files(((t_command *)(root->right))->outfiles, env);
        // printf("%s\n", env_expander((((t_command *)root->right))->command_arg->content, (((t_command *)root->right))->command_arg->index_list, env));
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
        return (globalVar);
}
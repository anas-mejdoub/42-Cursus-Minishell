/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:59:33 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 11:43:30 by amejdoub         ###   ########.fr       */
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
    
    print_tchbi7a();
    env = init_env(ev);
    t_elem *elem;
    while (1)
    {
        elem = lexer();
        if (!elem)
        {
            ft_alloc(0, NULL, FREE_ALL);
            continue;
        }
        t_command *root = parser(elem, env);

        t_exec_ret *r =  executor(root, env, '\0');

        
        int i = 0;
        int hehe= 0;
        if (!r || !r->pids)
        {
            ft_alloc(0, NULL, FREE_ALL);
            continue;
        }
        while (r && r->pids)
        {
            if (r->pids[i] == -1)
                break;
            waitpid(r->pids[i], &hehe, 0);
            if (WIFEXITED(hehe))
                g_var = WEXITSTATUS(hehe);
            else if (WIFSIGNALED(hehe))
                g_var = WTERMSIG(hehe) + 128;
            i++;
        }
        ft_alloc(0, NULL, FREE_ALL);
    }
    return (g_var);
}

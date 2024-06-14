/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:16:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/14 19:32:22 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char  **ev)
{
    (void)ac;
    (void)av;
    
    // t_global_data *global_data;
    t_env *env;
    t_elem *elem;

    // global_data = malloc(sizeof(t_global_data)); 
    env = init_env(ev);
    // global_data->env = env;
    while (1)
    {
        elem = lexer();
        while (elem)
        {
            printf("content :<%s>\n", elem->content);
            printf("state :<%s>\n", elem->state == 0 ? "IN_DQUOTE" : elem->state == 2 ? "GENERAL" : "IN_QUOTE");
            printf("token :<%c>\n", elem->type == -1 ? 'W' : (char)elem->type);
            printf("----------------------------------------------------\n");
            elem = elem->next;
        }
    }
    // env->set(&env->data, "test_env", "hhh");
    // while (env->data)
    // {
    //     printf("key :%s|    value %s\n", env->data->key, env->data->value);
    //     env->data = env->data->next;
    // }
}
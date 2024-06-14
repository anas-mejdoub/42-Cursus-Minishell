/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:16:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/12 19:50:26 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char  **ev)
{
    (void)ac;
    (void)av;
    
    // t_global_data *global_data;
    t_env *env;

    // global_data = malloc(sizeof(t_global_data)); 
    env = init_env(ev);
    // global_data->env = env;
    lexer();
    // env->set(&env->data, "test_env", "hhh");
    // while (env->data)
    // {
    //     printf("key :%s|    value %s\n", env->data->key, env->data->value);
    //     env->data = env->data->next;
    // }
}
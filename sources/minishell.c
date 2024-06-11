/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:16:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/11 17:31:10 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char  **ev)
{
    t_env *env;

    (void)ac;
    (void)av;
    env = init_env(ev);
    env->set(&env->data, "test_env", "hhh");
    while (env->data)
    {
        printf("key :%s|    value %s\n", env->data->key, env->data->value);
        env->data = env->data->next;
    }
}
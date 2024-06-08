/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:16:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/08 11:45:41 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char  **ev)
{
    t_env *env;

    (void)ac;
    (void)av;
    env = init_env(ev);
    printf("%s\n", env->get(env->data, "PATH"));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:15:58 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/30 19:09:38 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

void env_command(t_env *env)
{
    t_env_data *tmp;

    tmp = env->data;

    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp= tmp->next;
    }
}
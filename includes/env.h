/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:14:53 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/08 10:01:12 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_data
{
    char *key;
    char *value;
    struct s_env_data *next;
}   t_env_data;

typedef struct s_env
{
    t_env_data *data;
    char *(*get)(t_env_data *env, char *key);
    int (*set)(t_env_data **env, char *key, char *value);
    int (*unset)(t_env_data **env, char *key);
}   t_env;

t_env	*init_env(char **ev);

#endif
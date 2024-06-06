/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:58:04 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/06 16:50:29 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_env_infos
{
    char    *key;
    char    *value;
    void    *next;
}   t_env_infos;

typedef struct s_env
{
    t_env_infos    *env;
	t_env_infos    *(*init)(char **);
	int            (*get)(t_env_infos *, char *);
	int            (*set)(t_env_infos *, char *, char *);
}		t_env;

// int	get(char **env, char *key)
// {

// }

// int	set(char **env, char *key, char *value)
// {

// }

t_env	*init(char **ev)
{
    t_env *env;
    t_env_infos **head;
    t_env_infos *node;
    node = NULL;
    head = node;
    char  **arr;
    int   i;
    int   len;

    i = 0;
    while (ev && ev[len++])
    ;
    env = malloc(sizeof(t_env) * (len + 1));
    if (!env)
        return(NULL);
    
    i = 0;
    while (ev && ev[i])
    {
        arr = ft_split(ev[i], '=');
        
        if (!arr)
            return (NULL);
        if (i == 0)
        {
            node = malloc(sizeof(t_env_infos));
            if (!node)
                return (NULL);
        }
        else if (ev[i + 1])
        {
            node->next = malloc(sizeof(t_env_infos));
            if (!node)
                return (NULL);
        }
        else
            node->next = NULL;
        node->key = ft_strdup(arr[0]);
        node->value = ft_strdup(arr[1]);
        free (arr[0]);
        free (arr[1]);
        free (arr);
        node = node->next;
        i++;
    }
    return (env);
}

int main(int ac, char **av, char  **ev)
{
    t_env *env;
    env = init(ev);
}

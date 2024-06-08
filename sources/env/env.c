/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:58:04 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/08 12:01:57 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_env.h"

static int	allocate_node(int i, char **ev, t_env_data **node, t_env_data **tmp)
{
	if (i == 0)
	{
		*node = malloc(sizeof(t_env_data));
		if (!*node)
			return (1);
		*tmp = *node;
	}
	if ((ev && ev[i + 1]) || i == 0)
	{
		(*tmp)->next = malloc(sizeof(t_env_data));
		if (!*tmp)
			return (1);
	}
	else
		(*tmp)->next = NULL;
	return (0);
}

static int	fetch_env_data(char **ev, t_env_data **node, t_env_data **tmp,
		char **arr)
{
	int	i;

	i = 0;
	while (ev && ev[i])
	{
		arr = ft_split(ev[i], '=');
		if (!arr)
			return (1);
		if (allocate_node(i, ev, node, tmp))
			return (1);
		(*tmp)->key = ft_strdup(arr[0]);
		(*tmp)->value = ft_strdup(arr[1]);
		free(arr[0]);
		free(arr[1]);
		free(arr);
		*tmp = (*tmp)->next;
		i++;
	}
	return (0);
}

t_env	*init_env(char **ev)
{
	t_env		*env;
	t_env_data	*node;
	t_env_data	*tmp;
	char		**arr;
	int			i;
	int			len;

	node = NULL;
	tmp = NULL;
	node = NULL;
	tmp = NULL;
    arr = NULL;
	i = 0;
	len = 0;
	while (ev && ev[len++])
		;
	env = malloc(sizeof(t_env) * (len + 1));
	if (!env)
		return (NULL);
	if (fetch_env_data(ev, &node, &tmp, arr))
		return (NULL);
	env->data = node;
    init_env_methods(&env);
	return (env);
}

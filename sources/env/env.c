/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:58:04 by nbenyahy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/08 12:16:56 by nbenyahy         ###   ########.fr       */
=======
/*   Updated: 2024/07/08 12:26:57 by amejdoub         ###   ########.fr       */
>>>>>>> 8a47890b557a38578f51c6a2f6f7980fc24dc3a9
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

static int	fetch_env_data(char **ev, t_env_data **node, t_env_data **tmp)
{
	int	i;

	i = 0;
<<<<<<< HEAD
	if (!ev || !ev[0])
	{
		*node = NULL;
		*tmp = NULL;
=======
	if (ev == NULL)
	{
		*node = NULL;
		// *tmp = NULL;
>>>>>>> 8a47890b557a38578f51c6a2f6f7980fc24dc3a9
		return (0);
	}
	while (ev && ev[i])
	{
		int j = 0;
		while (ev[i][j] && ev[i][j] != '=')
			j++;
		if (allocate_node(i, ev, node, tmp))
			return (1);
		(*tmp)->key = ft_substr(ev[i], 0, j);
		(*tmp)->value = ft_substr(ev[i], j + 1, ft_strlen(ev[i] + j));
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
	int			len;

	node = NULL;
	tmp = NULL;
	node = NULL;
	tmp = NULL;
	len = 0;
	// if (!ev || !ev[0])
	// 	return (NULL);
	while (ev && ev[len++])
		;
	env = malloc(sizeof(t_env) * (len + 1));
	if (!env)
		return (NULL);
	if (fetch_env_data(ev, &node, &tmp))
		return (NULL);
	env->data = node;
    init_env_methods(&env);
	return (env);
}

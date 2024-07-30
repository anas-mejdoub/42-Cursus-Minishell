/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:58:04 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 11:36:17 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_env.h"

static int	allocate_node(int i, char **ev, t_envata **node, t_envata **tmp)
{
	if (i == 0)
	{
		*node = malloc(sizeof(t_envata));
		if (!*node)
			return (1);
		*tmp = *node;
	}
	if ((ev && ev[i + 1]) || i == 0)
	{
		(*tmp)->next = malloc(sizeof(t_envata));
		if (!*tmp)
			return (1);
	}
	else
		(*tmp)->next = NULL;
	return (0);
}

static int	fetch_env_data(char **ev, t_envata **node, t_envata **tmp)
{
	int	i;
	int	j;

	i = 0;
	if (ev == NULL)
	{
		*node = NULL;
		return (0);
	}
	while (ev && ev[i])
	{
		j = 0;
		while (ev[i][j] && ev[i][j] != '=')
			j++;
		if (allocate_node(i, ev, node, tmp))
			return (1);
		(*tmp)->key = ft_sabstr(ev[i], 0, j);
		(*tmp)->value = ft_sabstr(ev[i], j + 1, ft_strlen(ev[i] + j));
		*tmp = (*tmp)->next;
		i++;
	}
	return (0);
}

t_env	*init_env(char **ev)
{
	t_env		*env;
	t_envata	*node;
	t_envata	*tmp;
	int			len;

	node = NULL;
	tmp = NULL;
	node = NULL;
	tmp = NULL;
	len = 0;
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

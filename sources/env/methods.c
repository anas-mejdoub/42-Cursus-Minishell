/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:30:08 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/30 07:51:42 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_env.h"

static char	*get(t_envata *env, char *key)
{
	t_envata	*tmp;

	if (key && !ft_strncmp("?", key, 1) && ft_strlen(key) == 1)
		return (ft_itoa(g_var));
	if (!env || !key)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key))
			&& ft_strlen(tmp->key) == ft_strlen(key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	change_value(char *key, char *value, t_envata **tmp)
{
	while ((*tmp))
	{
		if ((!ft_strncmp((*tmp)->key, key, ft_strlen((*tmp)->key)))
			&& ft_strlen(key) == ft_strlen((*tmp)->key))
		{
			if (!value)
				return (0);
			free((*tmp)->value);
			(*tmp)->value = ft_strdap(value);
			return (0);
		}
		(*tmp) = (*tmp)->next;
	}
	return (1);
}

static int	set(t_envata **env, char *key, char *value)
{
	t_envata	*tmp;

	if (!key)
		return (1);
	tmp = *env;
	if (!change_value(key, value, &tmp))
		return (0);
	tmp = malloc(sizeof(t_envata));
	if (!tmp)
		return (1);
	tmp->key = ft_strdap(key);
	if (!value)
		tmp->value = NULL;
	else
		tmp->value = ft_strdap(value);
	tmp->next = *env;
	*env = tmp;
	return (2);
}

static int	unset(t_envata **env, char *key)
{
	t_envata	*tmp;
	t_envata	*prev;

	if (!*env || !key)
		return (1);
	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if ((!ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
			&& ft_strlen(key) == ft_strlen(tmp->key))
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (2);
}

void	init_env_methods(t_env **env)
{
	(*env)->get = get;
	(*env)->set = set;
	(*env)->unset = unset;
}

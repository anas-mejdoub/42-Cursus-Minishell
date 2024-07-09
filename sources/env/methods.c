/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:30:08 by nbenyahy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/08 13:00:24 by nbenyahy         ###   ########.fr       */
=======
/*   Updated: 2024/07/08 12:29:27 by amejdoub         ###   ########.fr       */
>>>>>>> 8a47890b557a38578f51c6a2f6f7980fc24dc3a9
/*                                                                            */
/* ************************************************************************** */

#include "local_env.h"

static char	*get(t_env_data *env, char *key)
{
	t_env_data	*tmp;

	if (!env || !key)
		return (NULL);
	tmp = env;
	if (key && !ft_strncmp("?", key, 1) && ft_strlen(key) == 1)
		return (ft_itoa(globalVar));
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) && ft_strlen(tmp->key) == ft_strlen(key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	set(t_env_data **env, char *key, char *value)
{
	t_env_data	*tmp;

	if (!key)
		return (1);
	tmp = *env;
	while (tmp)
	{
		if ((!ft_strncmp(tmp->key, key, ft_strlen(tmp->key))) && ft_strlen(key) == ft_strlen(tmp->key))
		{
			if (!value)
				return (0);
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = malloc(sizeof(t_env_data));
	if (!tmp)
		return (1);
	tmp->key = ft_strdup(key);
	if (!value)
		tmp->value = NULL;
	else
		tmp->value = ft_strdup(value);
	tmp->next = *env;
	*env = tmp;
	
	return (2);
}
static int	unset(t_env_data **env, char *key)
{
	t_env_data	*tmp;
	t_env_data	*prev;

	if (!*env || !key)
		return (1);
	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if ((!ft_strncmp(tmp->key, key, ft_strlen(tmp->key))) && ft_strlen(key) == ft_strlen(tmp->key))
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (2);
}

void init_env_methods(t_env **env)
{
    (*env)->get = get;
	(*env)->set = set;
	(*env)->unset = unset;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:40:06 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/29 15:12:48 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	my_rand(void)
{
	static int	r;

	if (!r)
		r = 1;
	r *= 50;
	return (r % INT_MAX);
}

char	*random_str(void)
{
	char	*charset;
	char	*res;
	int		key;
	int		i;
	int		rand;

	res = NULL;
	charset = ft_strdup(STR);
	i = 0;
	res = ft_alloc((sizeof(char) * 10), NULL, MALLOC);
	if (!res)
		return (NULL);
	while (i < 9)
	{
		rand = my_rand();
		if (rand < 0)
			rand = -rand;
		key = rand % 61;
		res[i] = charset[key];
		i++;
	}
	res[i] = '\0';
	ft_alloc(0, charset, FREE_PTR);
	charset = NULL;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:17:51 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/28 17:11:17 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_helper.h"

char	*ft_freed_join(char *s1, char *s2)
{
	char	*res;
	int		i;

	i = 0;
	// res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	res = ft_alloc(((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char)), NULL, MALLOC);
	if (!res)
		return (ft_alloc(0, s1, FREE_PTR), NULL);
		// return (free(s1), NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && *s2)
	{
		res[i] = *s2;
		s2++;
		i++;
	}
	res[i] = '\0';
	// free(s1);
	return (res);
}
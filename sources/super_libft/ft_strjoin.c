/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 22:51:47 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/28 16:47:25 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	concat(char const *s1, char const *s2, char *ptr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		ptr[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[j] = s2[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*ptr;

	if (!s2 || !s1)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ptr = (char *)ft_alloc((sizeof(char) * (s1len + s2len + 1)), NULL, MALLOC);
	if (!ptr)
		return (NULL);
	concat(s1, s2, ptr);
	return (ptr);
}

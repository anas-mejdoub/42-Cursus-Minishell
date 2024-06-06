/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:09 by nbenyahy          #+#    #+#             */
/*   Updated: 2023/12/16 21:16:19 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	org_dst_len;
	size_t	i;

	i = 0;
	dst_len = ft_strlen(dst);
	org_dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (ft_strlen(src) + size);
	while (src[i] != '\0' && dst_len < size - 1)
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
	}
	dst[dst_len] = '\0';
	return (org_dst_len + ft_strlen(src));
}

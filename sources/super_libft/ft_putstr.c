/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:08:25 by nbenyahy          #+#    #+#             */
/*   Updated: 2023/12/21 11:12:59 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *s, int *res)
{
	if (!s)
		return (ft_putstr("(null)", res));
	while (*s)
	{
		ft_putchar(*s, res);
		s++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 10:15:33 by nbenyahy          #+#    #+#             */
/*   Updated: 2023/12/21 12:21:35 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	helper(unsigned long nbr, char a, int *res)
{
	if (nbr < 10)
	{
		ft_putchar(nbr + 48, res);
	}
	else if (nbr < 16)
		ft_putchar(nbr + a - 10, res);
	else
	{
		helper(nbr / 16, a, res);
		helper((nbr % 16), a, res);
	}
}

void	ft_puthexa(unsigned long nbr, char a, int *res)
{
	if (a == 'x')
		helper(nbr, 'a', res);
	else if (a == 'X')
		helper(nbr, 'A', res);
	else if (a == 'p')
	{
		ft_putstr("0x", res);
		helper(nbr, 'a', res);
	}
}

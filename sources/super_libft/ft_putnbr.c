/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:16:40 by nbenyahy          #+#    #+#             */
/*   Updated: 2023/12/25 08:31:11 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long long n, int *res)
{
	if (n == -2147483648)
		ft_putstr("-2147483648", res);
	else if (n < 0)
	{
		ft_putchar('-', res);
		ft_putnbr(n * -1, res);
	}
	else if (n < 10)
		ft_putchar(n + '0', res);
	else if (n > 9)
	{
		ft_putnbr(n / 10, res);
		ft_putchar(n % 10 + '0', res);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:35:47 by taaraki           #+#    #+#             */
/*   Updated: 2023/03/27 15:36:07 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"utils.h"

static int	write_zero(void)
{
	write(1, "0", 1);
	return (1);
}

int	ft_print_address(unsigned long long x)
{
	const char	hex_lower[17] = "0123456789abcdef";
	int			nums[20];
	int			i;
	int			len;

	write(1, "0x", 2);
	i = 0;
	if (x == 0)
		return (2 + write_zero());
	while (x > 0)
	{
		nums[i] = x % 16;
		i++;
		x /= 16;
	}
	len = i;
	while (i > 0)
	{
		write(1, &hex_lower[nums[i - 1] % 16], 1);
		i--;
	}
	return (2 + len);
}

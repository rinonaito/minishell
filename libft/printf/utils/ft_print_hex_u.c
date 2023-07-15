/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:52:37 by taaraki           #+#    #+#             */
/*   Updated: 2023/03/27 15:34:58 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"utils.h"

static int	write_zero(void)
{
	write(1, "0", 1);
	return (1);
}

int	ft_print_hex_u(unsigned long long x)
{
	const char	hex_upper[17] = "0123456789ABCDEF";
	int			nums[20];
	int			i;
	int			len;

	if (x == 0)
		return (write_zero());
	i = 0;
	while (x > 0)
	{
		nums[i] = x % 16;
		i++;
		x /= 16;
	}
	len = i;
	while (i > 0)
	{
		write(1, &hex_upper[nums[i - 1] % 16], 1);
		i--;
	}
	return (len);
}

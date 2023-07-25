/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:29:53 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/26 19:36:07 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_ptr_hexpart(uintptr_t p, char *base)
{
	int		count;
	int		temp;
	size_t	base_len;

	base_len = ft_strlen(base);
	count = 0;
	if (p >= base_len)
	{
		temp = ft_print_ptr_hexpart(p / base_len, base);
		if (temp == -1)
			return (temp);
		count += temp;
	}
	temp = ft_print_char(base[p % base_len]);
	if (temp == -1)
		return (temp);
	count += temp;
	return (count);
}

int	ft_print_ptr(uintptr_t p)
{
	int	count;

	if (write(1, "0x", 2) == -1)
		return (-1);
	count = ft_print_ptr_hexpart(p, "0123456789abcdef");
	if (count == -1)
		return (-1);
	return (count + 2);
}

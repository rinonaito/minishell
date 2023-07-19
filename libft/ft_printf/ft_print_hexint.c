/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_hexa_l.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:28:30 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/26 19:35:05 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hexint(unsigned int nb, char *base)
{
	int		count;
	size_t	base_len;
	int		temp;

	count = 0;
	base_len = ft_strlen(base);
	if (nb >= base_len)
	{
		count += ft_print_hexint(nb / base_len, base);
		temp = ft_print_char(base[nb % base_len]);
		if (temp == -1)
			return (temp);
		count += temp;
	}
	else
	{
		temp = ft_print_char(base[nb % base_len]);
		if (temp == -1)
			return (temp);
		count += temp;
	}	
	return (count);
}

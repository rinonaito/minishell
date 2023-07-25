/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_dec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:55:27 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/26 19:33:49 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_negative(int nb, int count)
{
	int	temp;

	if (ft_print_char('-') == -1)
		return (-1);
	if (nb < -9)
	{
		temp = ft_print_decint(nb / 10 * -1);
		if (temp == -1)
			return (temp);
		count += temp;
	}
	temp = ft_print_char(nb % 10 * -1 + '0');
	if (temp == -1)
		return (temp);
	count += temp;
	return (count + 1);
}

static int	ft_print_positive(int nb, int count)
{
	int	temp;

	if (nb > 9)
	{
		temp = ft_print_decint(nb / 10);
		if (temp == -1)
			return (temp);
		count += temp;
	}
	temp = ft_print_char(nb % 10 + '0');
	if (temp == -1)
		return (temp);
	count += temp;
	return (count);
}

int	ft_print_decint(int nb)
{
	int	count;
	int	temp;

	count = 0;
	if (nb < 0)
	{
		temp = ft_print_negative(nb, count);
		if (temp == -1)
			return (temp);
		return (count + temp);
	}
	temp = ft_print_positive(nb, count);
	if (temp == -1)
		return (temp);
	return (count + temp);
}

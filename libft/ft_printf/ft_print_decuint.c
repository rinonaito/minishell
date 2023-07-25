/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint_dec.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:18:37 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/26 16:58:15 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_decuint(unsigned int nb)
{
	int	count;
	int	temp;

	count = 0;
	if (nb > 9)
	{
		temp = ft_print_decuint(nb / 10);
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

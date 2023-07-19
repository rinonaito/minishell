/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:26:31 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/23 12:30:41 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	ft_print_str(char *str)
{
	long	count;

	if (str == NULL)
		return (write(1, "(null)", 6));
	count = 0;
	while (str[count] != '\0')
	{
		if (write (1, &str[count], 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}

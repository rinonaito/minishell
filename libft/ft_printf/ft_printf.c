/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:07:02 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/26 19:45:23 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long	ft_check_type(va_list *lst, const char *fmt)
{
	int	count;

	count = 0;
	if (*fmt == 'c')
		count = ft_print_char((char)va_arg(*lst, int));
	else if (*fmt == 's')
		count = ft_print_str(va_arg(*lst, char *));
	else if (*fmt == 'p')
		count = ft_print_ptr((uintptr_t)va_arg(*lst, void *));
	else if (*fmt == 'd' || *fmt == 'i')
		count = ft_print_decint(va_arg(*lst, int));
	else if (*fmt == 'u')
		count = ft_print_decuint(va_arg(*lst, unsigned int));
	else if (*fmt == 'x')
		count = ft_print_hexint(va_arg(*lst, unsigned int), "0123456789abcdef");
	else if (*fmt == 'X')
		count = ft_print_hexint(va_arg(*lst, unsigned int), "0123456789ABCDEF");
	else if (*fmt == '%')
		count = ft_print_char('%');
	else
		count = ft_print_char(*fmt);
	return (count);
}

static long	ft_count_bytes(va_list *lst, const char *fmt)
{
	size_t	i;
	int		count;
	int		n;

	i = 0;
	count = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			i++;
			n = ft_check_type(lst, &fmt[i]);
			if (n == -1 || n > INT_MAX - count)
				return (-1);
			count += n;
		}
		else
		{
			if (write (1, &fmt[i], 1) == -1)
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	lst;	
	int		count;

	if (fmt == NULL)
		return (-1);
	va_start(lst, fmt);
	count = ft_count_bytes(&lst, fmt);
	va_end(lst);
	return (count);
}

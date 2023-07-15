/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:56:35 by taaraki           #+#    #+#             */
/*   Updated: 2023/06/18 20:18:28 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ft_printf.h"

static int	write_percent(void)
{
	write(1, "%", 1);
	return (1);
}

static void	pass_arg(va_list *ap, char c, int *index)
{
	if (c == 'c')
		*index += ft_putchar_i(va_arg(*ap, int));
	else if (c == 'd' || c == 'i')
		*index += ft_putnbr_i(va_arg(*ap, int));
	else if (c == 's')
		*index += ft_putstr_i(va_arg(*ap, char *));
	else if (c == 'p')
		*index += ft_print_address((unsigned long long)va_arg(*ap, void *));
	else if (c == 'u')
		*index += ft_putuint(va_arg(*ap, unsigned int));
	else if (c == 'x')
		*index += ft_print_hex((unsigned long long)va_arg(*ap, unsigned int));
	else if (c == 'X')
		*index += ft_print_hex_u((unsigned long long)va_arg(*ap, unsigned int));
	else if (c == '%')
		*index += write_percent();
}

static int	chr_in_str(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list		ap;	
	int			i;
	const char	format[] = "cspdiuxX%";

	if (s == NULL)
		return (0);
	va_start(ap, s);
	i = 0;
	while (*s)
	{
		if (*s == '%')
		{
			if (chr_in_str(format, *(++s)))
				pass_arg(&ap, *s++, &i);
			if (!*s)
				break ;
		}
		write(1, s++, 1);
		i++;
	}
	va_end(ap);
	return (i);
}

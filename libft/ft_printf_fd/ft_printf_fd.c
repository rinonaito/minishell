/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:56:35 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/03 20:44:05 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ft_printf_fd.h"

static int	write_percent(int fd)
{
	write(fd, "%", 1);
	return (1);
}

static void	pass_arg(int fd, va_list *ap, char c, int *index)
{
	if (c == 'c')
		*index += ft_putchar_i(fd, va_arg(*ap, int));
	else if (c == 'd' || c == 'i')
		*index += ft_putnbr_i(fd, va_arg(*ap, int));
	else if (c == 's')
		*index += ft_putstr_i(fd, va_arg(*ap, char *));
	else if (c == 'p')
		*index += ft_print_address(fd, (unsigned long long)va_arg(*ap, void *));
	else if (c == 'u')
		*index += ft_putuint(fd, va_arg(*ap, unsigned int));
	else if (c == 'x')
		*index += ft_print_hex_l(fd, (unsigned long long)va_arg(*ap, \
					unsigned int));
	else if (c == 'X')
		*index += ft_print_hex_u(fd, (unsigned long long)va_arg(*ap, \
					unsigned int));
	else if (c == '%')
		*index += write_percent(fd);
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

int	ft_printf_fd(int fd, const char *s, ...)
{
	const char	format[] = "cspdiuxX%";
	va_list		ap;	
	int			i;

	if (!s)
		return (0);
	va_start(ap, s);
	i = 0;
	while (*s)
	{
		if (*s == '%')
		{
			if (chr_in_str(format, *(++s)))
				pass_arg(fd, &ap, *s++, &i);
			if (!*s)
				break ;
			else if (*s == '%')
				continue ;
		}
		write(fd, s++, 1);
		i++;
	}
	va_end(ap);
	return (i);
}

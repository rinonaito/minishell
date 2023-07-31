/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:47:21 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/27 17:18:39 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"utils.h"

static void	putstr(int fd, const char *s)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

//count the digits of an int according to its base
static size_t	int_len(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	convert_int(int n, char s[], int sign)
{
	size_t	len_int;
	size_t	i;

	len_int = int_len(n);
	if (sign == -1)
		s[0] = '-';
	if (n == 0)
	{
		s[len_int + (sign == -1)] = '\0';
		return ;
	}
	i = 0;
	while (n != 0 && i < len_int)
	{
		s[len_int - i + (sign == -1) - 1] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	s[len_int + (sign == -1) + 1] = '\0';
}

//1.convert int into a number with the base 10
// - divide n once before making it positive to avoid overflow when == INT_MIN
//2.print the number
//3.return the number of digits plus the negative sign
int	ft_putnbr_i(int fd, int n)
{
	char	s[20];
	int		sign;
	size_t	len;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = int_len(n);
	s[len + (sign == -1) - 1] = sign * (n % 10) + '0';
	n /= 10;
	n *= sign;
	convert_int(n, s, sign);
	putstr(fd, s);
	return (len + (sign == -1));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:31:49 by taaraki           #+#    #+#             */
/*   Updated: 2023/03/27 15:33:24 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"utils.h"

static void	print_string(const char *s)
{
	if (s == NULL)
		return ;
	while (*s)
		write(1, s++, 1);
}

static size_t	int_len(int n)
{
	size_t	i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	check_negative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static int	check_exp(int nb)
{
	if (nb == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	else
	{
		write(1, "-2147483648", 11);
		return (11);
	}
}

int	ft_putnbr_i(int nb)
{
	size_t	len;
	size_t	i;
	int		neg_flag;
	char	str[12];

	neg_flag = 0;
	if (nb == 0 || nb == INT_MIN)
		return (check_exp(nb));
	else if (check_negative(nb))
	{
		nb = (-1) * nb;
		write(1, "-", 1);
		neg_flag = 1;
	}
	len = int_len(nb);
	i = 0;
	while (i < len)
	{
		str[len - i++ - 1] = (nb % 10) + '0';
		nb /= 10;
	}
	str[len] = '\0';
	print_string(str);
	return (len + neg_flag);
}

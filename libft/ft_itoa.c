/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:45:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/03/27 16:08:40 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digit(int n)
{
	size_t	count;

	count = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		count ++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		count ++;
	}
	return (count);
}

static char	*allocate_digit(char *new, int n, size_t count)
{
	while (count >= 0 && n > 0)
	{
		new[count] = n % 10 + '0';
		n = n / 10;
		count --;
	}
	return (new);
}

char	*ft_itoa(int n)
{
	char	*new;
	size_t	count;

	count = count_digit(n);
	new = (char *)malloc(sizeof(char) * (count + 1));
	if (new == NULL)
		return (NULL);
	new[count] = '\0';
	count --;
	if (n == -2147483648)
	{
		new[count] = '8';
		count --;
		n = -214748364;
	}
	if (n == 0)
		new[0] = '0';
	if (n < 0)
	{
		new[0] = '-';
		n = -n;
	}
	return (allocate_digit(new, n, count));
}

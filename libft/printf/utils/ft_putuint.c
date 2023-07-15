/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:31:49 by taaraki           #+#    #+#             */
/*   Updated: 2023/03/27 15:31:23 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"utils.h"

static void	print_str(char *s)
{
	while (*s)
		write(1, s++, 1);
}

static size_t	uint_len(unsigned int n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putuint(unsigned int nb)
{
	size_t	len;
	size_t	i;
	char	str[11];

	len = uint_len(nb);
	i = 0;
	while (i < len)
	{
		str[len - i - 1] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	str[len] = '\0';
	print_str(str);
	return ((int)len);
}

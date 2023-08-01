/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:31:49 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/27 17:16:24 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"utils.h"

static void	print_str(int fd, char *s)
{
	while (*s)
		write(fd, s++, 1);
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

int	ft_putuint(int fd, unsigned int nb)
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
	print_str(fd, str);
	return ((int)len);
}

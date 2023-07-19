/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:31:28 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/07 16:57:58 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	charcmp(const char *s1, const char *s2, size_t x)
{
	size_t	y;

	y = 0;
	while (y != x)
	{
		if (s1[y] != s2[y])
			return (((unsigned char *)s1)[y] - ((unsigned char *)s2)[y]);
		y ++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		answer;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' || s2[i] != '\0')
		i ++;
	if (n < i)
		answer = charcmp(s1, s2, n);
	else
		answer = charcmp(s1, s2, i);
	return (answer);
}

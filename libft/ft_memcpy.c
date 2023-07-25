/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:14:48 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/10 10:45:57 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*cdst;
	unsigned const char	*csrc;

	if (n == 0 || dst == src)
		return (dst);
	cdst = (unsigned char *)dst;
	csrc = (unsigned const char *)src;
	n --;
	while (n > 0)
	{
		cdst[n] = csrc[n];
		n --;
	}
	cdst[0] = csrc[0];
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:48:21 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/10 10:48:27 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*cdst;
	const char	*csrc;
	size_t		index;

	cdst = (char *)dst;
	csrc = (const char *)src;
	if (dst > src)
		ft_memcpy(dst, src, len);
	if (dst < src)
	{
		if (len == 0 || dst == src)
			return (dst);
		index = 0;
		while (index < len)
		{
			cdst[index] = csrc[index];
			index ++;
		}
	}
	return (dst);
}	

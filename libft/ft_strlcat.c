/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:52:04 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/08 22:11:30 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	else
	{
		i = 0;
		while (src[i] != '\0' && len_dst < dstsize - 1)
		{	
			dst[len_dst] = src[i];
			i ++;
			len_dst ++;
		}
		dst[len_dst] = '\0';
		return (len_dst + ft_strlen(&src[i]));
	}
}

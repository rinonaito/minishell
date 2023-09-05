/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:14:31 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/05 23:37:10 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	makestr(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = '\0';
	//dst[size] = '\0';
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (dstsize != 0)
	{
		if (dstsize - 1 > len_src)
			makestr(dst, src, len_src);
		else
			makestr(dst, src, dstsize - 1);
	}
	return (len_src);
}

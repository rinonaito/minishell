/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:55:14 by taaraki           #+#    #+#             */
/*   Updated: 2023/04/30 06:57:49 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*p1;
	char	*p2;
	size_t	len;
	size_t	return_val;

	p1 = (char *)dst;
	p2 = (char *)src;
	if (p1 == NULL)
		return (ft_strlen(p2));
	else
		len = ft_strlen(p1);
	if (dstsize <= len)
		return (ft_strlen(p2) + dstsize);
	return_val = len + ft_strlen(p2);
	while (*p2 && len < dstsize - 1)
	{
		p1[len] = *p2;
		p2++;
		len++;
	}
	p1[len] = '\0';
	return (return_val);
}

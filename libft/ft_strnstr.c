/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:54:01 by taaraki           #+#    #+#             */
/*   Updated: 2023/04/30 06:57:10 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*p1;
	char	*p2;
	size_t	len2;
	size_t	i;

	p1 = (char *)haystack;
	p2 = (char *)needle;
	len2 = ft_strlen(p2);
	if (*p2 == 0)
		return (p1);
	while (0 < len && *p1)
	{
		if (*p1 == p2[0])
		{
			i = 0;
			while (p1[i] == p2[i] && i < len)
				if (i++ == len2 - 1)
					return (p1);
		}
		p1++;
		len--;
	}	
	return (NULL);
}

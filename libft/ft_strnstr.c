/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:30:52 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/07 17:25:07 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i + j] != '\0')
	{
		if (haystack[i + j] == needle[0])
		{
			while (haystack[i + j] == needle[j] && len > i + j)
			{
				if (needle[j + 1] == '\0' && len > i + j)
					return ((char *)&haystack[i]);
				j ++;
			}
		}
		i ++;
		j = 0;
	}
	return (NULL);
}

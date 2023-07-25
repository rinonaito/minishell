/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:51:14 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/07 16:12:09 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*cs;

	i = ft_strlen(s);
	if (c == '\0')
	{
		cs = (char *)&s[i];
		return (cs);
	}
	while (i > 0)
	{
		if (s[i] == (char)c)
		{
			cs = (char *)&s[i];
			return (cs);
		}
		i --;
	}
	if (s[0] == (char)c)
		return ((char *)s);
	return (NULL);
}

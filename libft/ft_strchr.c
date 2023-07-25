/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:43:19 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/07 16:50:28 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*cs;
	size_t	len_s;

	if (c == '\0')
	{
		len_s = ft_strlen(s);
		cs = (char *)&s[len_s];
		return (cs);
	}
	else
	{
		i = 0;
		while (s[i] != '\0')
		{
			if (s[i] == (char)c)
			{
				cs = (char *)&s[i];
				return (cs);
			}
			i ++;
		}
		return (NULL);
	}
}

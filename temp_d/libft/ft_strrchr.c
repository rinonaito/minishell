/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:55:24 by taaraki           #+#    #+#             */
/*   Updated: 2023/03/14 15:32:55 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	bool	exists;

	p = (char *)s;
	exists = false;
	while (*s)
	{
		if (*s == (char)c)
		{
			p = (char *)s;
			exists = true;
		}
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	if (exists)
		return (p);
	return (NULL);
}

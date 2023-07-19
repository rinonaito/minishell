/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:09:02 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/09 14:27:51 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*cs;
	unsigned char		cc;
	void				*vs;
	size_t				i;

	cs = (unsigned char *)s;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (cs[i] == cc)
		{
			vs = (void *)&cs[i];
			return (vs);
		}
		i ++;
	}
	return (NULL);
}

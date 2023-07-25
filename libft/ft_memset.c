/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:56:42 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/10 10:47:03 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ucb;
	unsigned char	ucc;

	ucb = (unsigned char *)b;
	ucc = (unsigned char)c;
	if (len == 0)
		return (b);
	len --;
	while (len > 0)
	{
		ucb[len] = ucc;
		len --;
	}
	ucb[0] = ucc;
	return (b);
}

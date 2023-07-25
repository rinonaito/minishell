/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:55:40 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/09 15:49:31 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(src);
	new = (char *)malloc (sizeof (const char) * (size + 1));
	if (new == NULL)
		return (NULL);
	else
	{
		while (src[i] != '\0')
		{
			new[i] = src[i];
			i ++;
		}
		new[i] = '\0';
		return (new);
	}
}

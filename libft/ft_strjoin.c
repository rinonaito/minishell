/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:05:07 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/09 16:50:30 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	total_len;
	char	*joined_str;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = (char *)malloc (sizeof (const char) * (total_len + 1));
	if (joined_str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		joined_str[i] = s1[i];
		i ++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		joined_str[i + j] = s2[j];
		j ++;
	}
	joined_str[j + i] = '\0';
	return (joined_str);
}

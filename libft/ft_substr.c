/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:25:27 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/11 13:28:00 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_strndup(const char *src, size_t new_len)
{
	size_t		i;
	char		*sub_s;

	sub_s = (char *)malloc (sizeof (const char) * (new_len + 1));
	if (sub_s == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (i < new_len)
		{
			sub_s[i] = src[i];
			i ++;
		}
		sub_s[i] = '\0';
		return (sub_s);
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	new_len;
	char	*sub_s;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		new_len = 0;
	else
	{
		if (ft_strlen(s) - (size_t)start < len)
			new_len = ft_strlen(s) - (size_t)start;
		else
			new_len = len;
	}
	sub_s = ft_strndup(&s[start], new_len);
	return (sub_s);
}

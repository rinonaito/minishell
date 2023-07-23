/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:52:18 by taaraki           #+#    #+#             */
/*   Updated: 2023/04/30 06:56:56 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	char	*temp;
	size_t	len_new;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	len_new = len;
	if (ft_strlen(s) - (size_t)start < len)
		len_new = ft_strlen(s) - (size_t)start;
	s += start * sizeof(char);
	p = (char *)malloc(sizeof(char) * (len_new + 1));
	if (p == NULL)
		return (NULL);
	temp = p;
	while (len_new)
	{
		*p++ = *(char *)s++;
		len_new--;
	}
	*p = '\0';
	return (temp);
}

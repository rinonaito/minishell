/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:53:52 by taaraki           #+#    #+#             */
/*   Updated: 2023/03/11 13:28:42 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	char	*temp;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (p == NULL)
		return (NULL);
	temp = p;
	while (*s1)
		*(p++) = *(char *)(s1++);
	while (*s2)
		*(p++) = *(char *)(s2++);
	*p = '\0';
	return (temp);
}

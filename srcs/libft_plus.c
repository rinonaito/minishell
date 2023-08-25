/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:14:00 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/25 14:23:24 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//@func:  check if two strings are exactly the same
//@usage:
//		if (ft_strnequ(s1, s2))
//			printf("s1 and s2 are identical\n");
//@return_val:
//		1 if they're identical, and 0 if not
int	ft_strequ(const char *s1, const char *s2)
{
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1);
	if (len != ft_strlen(s2))
		return (0);
	if (ft_strncmp(s1, s2, len) == 0)
		return (1);
	return (0);
}

char	*ft_strndup(char *str, size_t len)
{
	char	*new;
	size_t	i;

	if (!str || len == 0)
		return (NULL);
	new = malloc(sizeof(char) * len + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

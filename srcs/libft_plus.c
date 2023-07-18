/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:14:00 by rnaito            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/17 17:03:54 by taaraki          ###   ########.fr       */
=======
/*   Updated: 2023/07/11 23:54:18 by taaraki          ###   ########.fr       */
>>>>>>> 2bc9ac71d95391bccb992b660ad6d615b4a8ba09
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//@func:  check if two strings are exactly the same
//@usage:
//		if (ft_strnequ(s1, s2))
//			printf("s1 and s2 are identical\n");
//@return_val:
//		1 if they're identical, and 0 if not
<<<<<<< HEAD
int	ft_strequ(const char *s1, const char *s2)
=======
int	ft_strnequ(const char *s1, const char *s2)
>>>>>>> 2bc9ac71d95391bccb992b660ad6d615b4a8ba09
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

	if (!str)
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

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (str1[i] == str2[i])
		return (0);
	return (1);
}

char	*ft_strchrchr(char *str, char c1, char c2, int *not_closed)
{
	size_t	i;
	char	*new_start;

	new_start = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		new_start = ft_skip_to_closing_quote(&str[i], not_closed);
		if (new_start != NULL)
			i += new_start - &str[i];
		if (str[i] == c1 || str[i] == c2)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

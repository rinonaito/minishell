/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:56:08 by taaraki           #+#    #+#             */
/*   Updated: 2023/04/30 06:56:30 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

//return 0 or 1 to determine if the character should be trimmed
static int	trimmed(char const *haystack, char c)
{
	char	*p;

	p = (char *)haystack;
	while (*p)
	{
		if (*p == c)
			return (1);
		p++;
	}
	return (0);
}

//return the index to start copying the string
static size_t	count_begin(char const *haystack, char const *needle)
{
	char	*p;
	size_t	i_begin;

	p = (char *)haystack;
	i_begin = 0;
	while (*p)
	{
		if (trimmed(needle, *p))
			i_begin++;
		else
			break ;
		p++;
	}
	return (i_begin);
}

//return the index to end copying the string (counting from the end)
static size_t	count_end(char const *haystack, char const *needle)
{
	char	*p;
	size_t	i_end;
	size_t	len;

	p = (char *)haystack;
	len = 1;
	if (ft_strlen(p) > 1)
		len = ft_strlen(p);
	p = &p[len - 1];
	i_end = 0;
	while (*p)
	{
		if (trimmed(needle, *p))
			i_end++;
		else
			break ;
		p--;
	}
	return (i_end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	i_begin;
	size_t	i_end;
	size_t	len_new;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	else if (set == NULL)
		return (ft_strdup(s1));
	i_begin = count_begin(s1, set);
	i_end = count_end(s1, set);
	len_new = 0;
	if (ft_strlen(s1) > i_begin + i_end)
		len_new = ft_strlen(s1) - i_begin - i_end;
	new = (char *)malloc(sizeof(char) * (len_new + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len_new)
		new[i++] = s1[i_begin++];
	new[len_new] = '\0';
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:44:10 by rnaito            #+#    #+#             */
/*   Updated: 2023/04/18 20:34:34 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_each_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i ++;
	return (i);
}

static int	count_element(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 1;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && i != 0 && s[i + 1] != '\0' && s[i + 1] != c)
			count ++;
		i ++;
	}
	return (count);
}

static int	free_memory(char *temp, size_t element, char **new)
{
	if (temp == NULL)
	{
		element --;
		while (element > 0)
		{
			free(new[element]);
			element --;
		}
		free(new[element]);
		free(new);
		return (0);
	}
	return (1);
}

static char	*allocate_string(const char *p_each, char c,
			size_t element, char **new)
{
	char	*temp;
	size_t	len;

	len = count_each_len(p_each, c);
	temp = NULL;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (free_memory(temp, element, new) == 0)
		return (NULL);
	ft_memcpy((char *)temp, (const char *)p_each, len);
	temp[len] = '\0';
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	char		**new;
	size_t		element;
	size_t		i;
	size_t		j;

	if (s == NULL)
		return (NULL);
	element = count_element(s, c);
	new = (char **)malloc(sizeof(char *) * (element + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0' && j < element)
	{
		if (s[i] != c)
		{
			new[j] = allocate_string(&s[i], c, element, new);
			i = i + count_each_len(&s[i], c);
			j ++;
		}
		i ++;
	}
	new[j] = NULL;
	return (new);
}

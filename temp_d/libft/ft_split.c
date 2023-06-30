/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:40:45 by taaraki           #+#    #+#             */
/*   Updated: 2023/04/30 06:59:20 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

//count the length of letters split by splitter or null terminator
static size_t	count_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

//check if the letters to split exist
static int	exist_letters(const char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			return (1);
		i++;
	}
	return (0);
}

//counting the number of splitters if there's letters to split
static int	count_split(const char *s, char c)
{
	size_t	i_split;
	size_t	len;

	i_split = 0;
	while (*s)
	{	
		len = count_len(s, c);
		s += len;
		if (len != 0 && *s == c && exist_letters(s, c))
			i_split++;
		if (len == 0)
			s++;
	}
	return (i_split);
}

static int	split_success(char const *s, char **new, size_t array_size, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (i < array_size)
	{
		if (*s == '\0')
			break ;
		len = count_len(s, c);
		if (len == 0)
		{
			s++;
			continue ;
		}
		new[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (new[i] == NULL)
			return (0);
		j = 0;
		while (j < len)
			new[i][j++] = *s++;
		new[i++][j] = '\0';
		s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	array_size;
	size_t	i;

	if (!s)
		return (NULL);
	array_size = count_split(s, c) + exist_letters(s, c);
	new = (char **)malloc(sizeof(char *) * (array_size + 1));
	if (new == NULL)
		return (NULL);
	if (!split_success(s, new, array_size, c))
	{
		i = 0;
		while (new[i])
		{
			free(new[i]);
			new[i] = NULL;
		}
		free(new);
		new = NULL;
		return (NULL);
	}
	new[array_size] = NULL;
	return (new);
}

/*
int	main(void)
{
	//char **tab = ft_split("  tripouille  42  ", ' ');
	//char **tab = ft_split("tripouille", 0);
	//char **tab = ft_split("     ", ' ');
	char **tab = ft_split("", ' ');
	    
	printf("tab:%s", tab[0]);
	return (0);
}
*/

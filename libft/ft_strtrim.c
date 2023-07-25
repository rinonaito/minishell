/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:14:09 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/15 10:14:27 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_included(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i ++;
	}
	return (0);
}

static size_t	ft_check_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start] != '\0')
	{
		if (ft_is_included(s1[start], set) == 1)
			start ++;
		else
			break ;
	}
	return (start);
}

static size_t	ft_check_goal(char const *s1, char const *set, size_t start)
{
	size_t	goal;

	goal = ft_strlen(s1);
	while (goal > start)
	{
		if (ft_is_included(s1[goal - 1], set) == 1)
			goal --;
		else
			break ;
	}
	return (goal);
}

char	*ft_strtrim(char const *s1, char const*set)
{
	size_t		start;
	size_t		goal;
	size_t		new_len;
	char		*new;
	size_t		a;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = ft_check_start(s1, set);
	goal = ft_check_goal(s1, set, start);
	new_len = goal - start;
	new = (char *)malloc(sizeof(char const) * (new_len + 1));
	if (new == NULL)
		return (NULL);
	a = 0;
	while (a < new_len)
	{
		new[a] = s1[start];
		a ++;
		start ++;
	}
	new[a] = '\0';
	return (new);
}

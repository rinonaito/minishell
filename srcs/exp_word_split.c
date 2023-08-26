/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_word_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:28:26 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/26 16:25:05 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	for_the_beginning(char *space_char, char *ifs, char *after_split, char *before_split)
{
	size_t	len_of_beginning;

	len_of_beginning = 0;
	while (ft_strchr(ifs, *before_split) != NULL && *before_split != '\0')
	{
		if (ft_strchr(space_char, *before_split) == NULL)
		{
			*after_split = ' ';
			after_split++;
		}
		before_split++;
		len_of_beginning++;
	}
	return (len_of_beginning);
}

int	ft_split_with_ifs(char *space_char, char **old, size_t *i, char *new)
{
	//区切り文字だが空白文字ではないので、区切り文字をスペースに変換する
	if (ft_strchr(space_char, (*old)[*i]) == NULL)
		(*i)++;
	//区切り文字かつ空白文字なので省略する
	else
	{
		while (ft_strchr(space_char, (*old)[*i]) != NULL && (*old)[*i] != '\0')
			(*i)++;
		if ((*old)[*i] == '\0')
			return (1);
	}
	*new = ' ';
	return (0);
}

static void	for_the_rest(char *space_char, char *ifs, char **new, char *old)
{
	size_t	i;
	size_t	j;
	char	*closing_quote;

	i = 0;
	j = ft_strlen(*new);
	while (old[i] != '\0')
	{
		closing_quote = skip_to_closing_quote(&old[i]);
		if (closing_quote == NULL)
			closing_quote = &old[i];
		while (&old[i] < closing_quote && old[i] != '\0')
			(*new)[j++] = old[i++];
		//区切り文字でない場合
		if (ft_strchr(ifs, old[i]) == NULL)
			(*new)[j] = old[i++];
		//区切り文字の場合
		else
		{
			
			if (ft_split_with_ifs(space_char, &old, &i, &(*new)[j]) == 1)
				break ;
		}
		j++;
	}
}

static char	*split_val(char *ifs, char *before_split, char *space_charset)
{
	char	*after_split;
	size_t	len_of_beginning;

	after_split = ft_calloc(ft_strlen(before_split) + 1, sizeof(char));
	if (after_split == NULL)
		return (NULL);
	len_of_beginning = for_the_beginning(space_charset, ifs, after_split, before_split);
	for_the_rest(space_charset, ifs, &after_split, &before_split[len_of_beginning]);
	return (after_split);
}

char	*split_expanded_word(char *before_split, t_env *env_lst)
{
	char	*ifs;
	char	*space_charset;
	char	*after_split;

	printf("before_split = %s\n", before_split);
	space_charset = " \t\n\0";
	ifs = my_getenv("IFS", env_lst);
	if (ifs == NULL)
		ifs = space_charset;
	after_split = split_val(ifs, before_split, space_charset);
	return (after_split);
}

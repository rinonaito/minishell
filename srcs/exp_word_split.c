/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_word_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:28:26 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/25 00:11:41 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_for_start(char *space_char, char *ifs, char **new, char *old)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ft_strchr(ifs, old[i]) != NULL && old[i] != '\0')
	{
		if (ft_strchr(space_char, old[i]) == NULL)
		{
			(*new)[j] = ' ';
			j++;
		}
		i++;
	}
	return (i);
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

void	ft_for_middle(char *space_char, char *ifs, char **new, char *old)
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
		printf("old[%zu]=%c\n", i, old[i]);
		printf("new[%zu]=%c\n", j, (*new)[j]);
		j++;
	}
}

char	*ft_split_token(char *ifs, char *old, char *space_charset)
{
	char	*new;
	size_t	i;

	new = ft_calloc(ft_strlen(old) + 1, sizeof(char));
	i = ft_for_start(space_charset, ifs, &new, old);
	ft_for_middle(space_charset, ifs, &new, &old[i]);
	return (new);
}

char	*split_expanded_word(char *before_split, t_env *env_lst)
{
	char	*ifs;
	char	*space_charset;
	char	*after_split;

	space_charset = " \t\n\0";
	ifs = my_getenv("IFS", env_lst);
	if (ifs == NULL)
	{
		printf("ifs is NULL\n");
		ifs = space_charset;
	}
	after_split = ft_split_token(ifs, before_split, space_charset);
	return (after_split);
}

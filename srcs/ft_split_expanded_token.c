/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expanded_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:28:29 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/14 23:21:14 by rnaito           ###   ########.fr       */
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
	if (ft_strchr(space_char, (*old)[*i]) == NULL)
		(*i)++;
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
		closing_quote = ft_skip_to_closing_quote(&old[i]);
		if (closing_quote == NULL)
			closing_quote = &old[i];
		while (&old[i] < closing_quote && old[i] != '\0')
			(*new)[j++] = old[i++];
		if (ft_strchr(ifs, old[i]) == NULL)
			(*new)[j] = old[i++];
		else
		{
			if (ft_split_with_ifs(space_char, &old, &i, &(*new)[j]) == 1)
				break ;
		}
		j++;
	}
}

char	*ft_split_token(char *ifs, char *old)
{
	char	*new;
	char	*space_char;
	size_t	i;

	space_char = " \t\n";
	new = ft_calloc(ft_strlen(old) + 1, sizeof(char));
	i = ft_for_start(space_char, ifs, &new, old);
	ft_for_middle(space_char, ifs, &new, &old[i]);
	return (new);
}

void	ft_split_expanded_token(t_token *param)
{
	char	*ifs;
	char	*new_token;
	char	*old_token;

	ifs = getenv("IFS");
	if (ifs == NULL)
		ifs = " \t\n";
//	ifs = "/";
//	printf("ifs = %s\n", ifs);
	while (param != NULL)
	{
		old_token = param->token;
		new_token = ft_split_token(ifs, old_token);
		free (old_token);
		param->token = new_token;
		param = param->next;
	}
}

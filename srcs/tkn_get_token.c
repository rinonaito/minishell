/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_get_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:55:59 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/05 21:04:38 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_composed_by_space(char *token)
{
	size_t	i;
	char	*space_charset;

	space_charset = " \t\n";
	i = 0;
	while (token[i] != '\0')
	{
		if (ft_strchr(space_charset, token[i]) == NULL)
			return (false);
		i++;
	}
	return (true);
}

static char	*get_token_start(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (&line[i]);
}

char	*get_token(char **line, int *is_error)
{
	char	*token_start;
	char	*token_end;
	char	*token;

	token = NULL;
	token_start = get_token_start(*line);
	token_end = get_token_end(token_start);
	if (token_end == NULL)
	{
		*is_error = 1;
		*line = NULL;
		return (NULL);
	}
	token = ft_strndup(token_start, token_end - token_start);
	if (is_composed_by_space(token))
	{
		free (token);
		token = NULL;
	}
	*line = token_end;
	return (token);
}

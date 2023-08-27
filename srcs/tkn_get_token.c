/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_get_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:55:59 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/25 18:31:00 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_token_start(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (&line[i]);
}

char	*get_token(char **line)
{
	char	*token_start;
	char	*token_end;
	char	*token;

	token_start = get_token_start(*line);
	token_end = get_token_end(token_start);
	token = ft_strndup(token_start, token_end - token_start);
	*line = token_end;
	if (token != NULL && ft_strlen(token) == 0)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

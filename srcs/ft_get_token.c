/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:31:20 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/11 18:38:50 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_skip_space(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (&line[i]);
}

char	*ft_find_operator(char *start, char *end)
{
	size_t	i;
	size_t	len;
	char	*new_start;

	i = 0;
	len = end - start;
	while (i < len)
	{
		new_start = ft_skip_to_closing_quote(&start[i]);
		if (new_start == NULL)
			return (NULL);
		else
			i += new_start - &start[i];
		if (start[i] == '|' || start[i] == '<' || start[i] == '>')
			return (&start[i]);
		i++;
	}
	return (end);
}

char	*ft_start_with_operator(char *start)
{
	char	*end;

	end = NULL;
	if (*start == '|')
		end = start + 1;
	if (*start == '>')
	{
		if (*(start + 1) == '>')
			end = start + 2;
		else
			end = start + 1;
	}
	if (*start == '<')
	{
		if (*(start + 1) == '<')
			end = start + 2;
		else
			end = start + 1;
	}
	return (end);
}

char	*ft_skip_to_closing_quote(char *old_start)
{
	char	*closing_quote;

	closing_quote = NULL;
	if (old_start == NULL)
		return (NULL);
	if (*old_start == '\'' || *old_start == '\"')
	{
		closing_quote = ft_strchr(old_start + 1, *old_start);
		return (closing_quote);
	}
	return (old_start);
}

char	*ft_get_token(char **line)
{
	char	*start;
	char	*end;
	char	*token;

	start = ft_skip_space(*line);
	end = ft_start_with_operator(start);
	if (end == NULL)
	{
		end = ft_find_endoftoken(start);
		end = ft_find_operator(start, end);
	}
	if (end == NULL)
		end = ft_find_endoftoken(start);
	*line = end;
	token = ft_strndup(start, end - start);
	if (token != NULL && ft_strlen(token) == 0)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

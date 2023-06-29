/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:31:20 by rnaito            #+#    #+#             */
/*   Updated: 2023/06/29 13:49:07 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_space(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	return (&line[i]);
}

char	*ft_find_operator(char *start, char *end)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = end - start;
	while (i < len)
	{
		if (start[i] == '|' || start[i] == '<' || start[i] == '>')
			return (&start[i]);
		i++;
	}
	return (end);
}

char	*ft_start_with_metachar(char *start, char *end)
{
	if (end == NULL)
	{
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
	}
	return (end);
}

char	*ft_start_with_quote(char *start)
{
	char	*end;

	end = NULL;
	if (*start == '\'' || *start == '\"')
	{
		end = ft_strchr(start + 1, *start);
		if (end != NULL)
			end++;
	}
	return (end);
}

char	*ft_get_token(char **line)
{
	char	*start;
	char	*end;
	char	*token;

	*line = skip_space(*line);
	start = *line;
	end = ft_start_with_quote(start);
	end = ft_start_with_metachar(start, end);
	if (end == NULL)
	{
		end = ft_strchrchr(start, ' ', '	');
		if (end == NULL)
			end = ft_strchr(start, '\0');
		end = ft_find_operator(start, end);
	}
	*line = end;
	if (*end == '\0')
		*line = NULL;
	token = ft_strndup(start, end - start);
	return (token);
}

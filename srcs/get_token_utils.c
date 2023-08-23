/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:56:19 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/23 12:57:52 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*for_token_end_with_ifs(char *str)
{
	size_t	i;
	char	*new_start;

	new_start = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		new_start = ft_skip_to_closing_quote(&str[i]);
		if (new_start != NULL)
			i += new_start - &str[i];
		if (str[i] == ' ' || str[i] == '\t')
			return (&str[i]);
		i++;
	}
	return (&str[i]);
}

static char	*for_token_end_with_operator(char *start, char *end)
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
			return (end);
		else
			i += new_start - &start[i];
		if (start[i] == '|' || start[i] == '<' || start[i] == '>')
			return (&start[i]);
		i++;
	}
	return (end);
}

static char	*get_end_for_operator_token(char *start)
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

static char	*get_end_for_word_token(char *token_start)
{
	char	*token_end;

	token_end = for_token_end_with_ifs(token_start);
	token_end = for_token_end_with_operator(token_start, token_end);
	return (token_end);
}
		
char	*get_token_end(char *token_start)
{
	char	*token_end;

	token_end = get_end_for_operator_token(token_start);
	if (token_end == NULL)
		token_end = get_end_for_word_token(token_start);
	return (token_end);
}

char	*get_token_start(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (&line[i]);
}

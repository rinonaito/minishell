/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/06/28 19:28:40 by rnaito           ###   ########.fr       */
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

char	*ft_get_token(char **line)
{ char	*start;
	char	*end;
	char	*token;

	*line = skip_space(*line);
	start = *line;
	end = NULL;
	if (**line == '\'' || **line == '\"')	
	{
		end = ft_strchr(*line + 1, **line);
		if (end != NULL)
			end++;
	}
	if (end == NULL)
		end = ft_strchrchr(*line, ' ', '	');
	if (end != NULL)
	{
		token = ft_strndup(start, end - start);
		*line = end;
	}
	else
	{
		token = ft_strndup(start, ft_strlen(start));
		*line = NULL;
	}
	return (token);
}

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (str1[i] == str2[i])
		return (0);
	return (1);
}

int	ft_check_token_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (TK_OPERATOR);
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0)
		return (TK_OPERATOR);
	if (ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0)
		return (TK_OPERATOR);
	return (TK_WORD);
}


t_token *ft_tokenize(char *line)
{	
	char	*token;
	t_token *head;
	t_token *new;
	int		type;
	
	if (line != NULL)
		head = ft_lstnew_ms(NULL, 0);
	while (line != NULL)
	{
		token = ft_get_token(&line);
		type = ft_check_token_type(token);
		new = ft_lstnew_ms(token , type);
		ft_lstadd_back_ms(&head, new);
	}
	return (head);	
}

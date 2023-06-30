/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:31:20 by rnaito            #+#    #+#             */
/*   Updated: 2023/06/29 22:32:24 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//@func: check the string from the beggining and
//advance the poninter as long as the char is space or tab.
//@param:
//	char *line: head pointer of the string to be checked
//@return_val: pointer of the first non-space char
char	*skip_space(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	return (&line[i]);
}

//@func: search if there is metachar (|, >, <) between start and end.
//@param:
//	char *start: pointer of the beginning of string
//	char *end  : pointer of the end of string
//@return_val: if the string has metachar, pointer of the metacharacter
//	if not, return pointer of the parameter "end" as it is.
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

//@func: check if this token is composed of metacharacter or not
//@param:
//		char *start: pointer of the beginning of the string
//		char *end  : pointer of the end of the string
//@return_val:if the token is metacharacter, return the pointer just after
//	the end of token this token. If not, return the parameter "end" as it is.
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

//@func: check if this token is quoted or not
//@param: 
//	char *start: pointer of the beginning of the token 
//@return_val: If this token is quoted, return the pointer just after
//the end of the closing quotation. If not, return NULL.
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


//@func: split the parameter accorning to the definition of "token" in Bash.
//@param:
//	char **line: pointer of the input string
//@return_val: pointer of the duplicated string of a token
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

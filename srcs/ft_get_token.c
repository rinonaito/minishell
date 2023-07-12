/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:31:20 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/12 14:20:42 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//@func: check the string from the beggining and
//advance the poninter as long as the char is space or tab.
//@param:
//	char *line: head pointer of the string to be checked
//@return_val: pointer of the first non-space char
char	*ft_skip_space(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (&line[i]);
}

//@func: search if there is operator (|, >, <) between start and end.
//@param:
//	char *start: pointer of the beginning of string
//	char *end  : pointer of the end of string
//@return_val: if the string has operator(not quoted),
//	pointer of the operator.
//	if not, return pointer of the parameter "end" as it is.
//	return NULL incase of quotation error.
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

//@func: check if this token is composed of operator or not
//@param:
//		char *start: pointer of the beginning of the string
//		char *end  : pointer of the end of the string
//@return_val:if the token is operator, return the pointer just after
//	the end of token this token. If not, return the parameter "end" as it is.
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

//@func: if the parameter char *old_start starts with quotation, 
//skip the pointer to the closing quote.
//return if the quotation is properly closed, the pointer of the closing quote.
//If not, return NULL. if 
//@param:
//	char *old_start: pointer of the head pointer of the string token
//@return_val: return the param"old_start" if there is no quotation
//return pointer just after the quotation when the string has
//quotation and is closed. if not closed, return NULL.
char	*ft_skip_to_closing_quote(char *old_start)
{
	char	*closing_quote;

	closing_quote = NULL;
	if (*old_start == '\'' || *old_start == '\"')
	{
		closing_quote = ft_strchr(old_start + 1, *old_start);
		return (closing_quote);
	}
	return (old_start);
}

//@func: split the parameter accorning to the definition of "token" in Bash.
//@param:
//	char **line: pointer of the input string
//	int	*not_closed: flag to check if the quotation is properly closed
//@return_val: return pointer of the duplicated string of a token
//return NULL if quotation is not closed or the input is only space
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

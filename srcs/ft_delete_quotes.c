/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:06:49 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/31 18:04:40 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_token_sin_quotes(char *with_quotes)
{
	size_t	i;
	size_t	j;
	char	*sin_quotes;
	char	*closing_quote;

	i = 0;
	j = 0;
	sin_quotes = ft_calloc(ft_strlen(with_quotes) + 1, sizeof(char));
	while (with_quotes[i] != '\0')
	{
		closing_quote = ft_skip_to_closing_quote(&with_quotes[i]);
		if (closing_quote == NULL || closing_quote == &with_quotes[i])
			sin_quotes[j++] = with_quotes[i++];
		else
		{
			i++;
			while (&with_quotes[i] != closing_quote)
				sin_quotes[j++] = with_quotes[i++];
			i++;
		}
	}
	return (sin_quotes);
}

void	ft_delete_quotes(t_token *param)
{
	char	*with_quotes;
	char	*sin_quotes;

	while (param != NULL && param->type != TK_PIPE)
	{
		with_quotes = param->token;
		if (with_quotes != NULL)
		{
			sin_quotes = ft_get_token_sin_quotes(with_quotes);
			free (with_quotes);
			param->token = sin_quotes;
		}
		param = param->next;
	}
}

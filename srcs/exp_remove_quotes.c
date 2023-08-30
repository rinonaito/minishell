/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_remove_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:37:12 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/31 00:53:57 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	exist_closing_quote(char *current_quote, char *closing_quote)
{
	if (current_quote == closing_quote)
		return (false);
	if (closing_quote == NULL)
		return (false);
	return (true);
}

static int	set_content_of_quotations(char *opening_quote,
				char *closing_quote, char *without_quotes)
{
	int	len_of_content;

	len_of_content = 0;
	opening_quote++;
	while (opening_quote != closing_quote && *opening_quote != '\n')
	{
		*without_quotes = *opening_quote;
		without_quotes++;
		opening_quote++;
		len_of_content++;
	}
	return (len_of_content);
}

char	*remove_quotes(char *with_quotes)
{
	size_t	i;
	size_t	j;
	size_t	len_of_content;
	char	*without_quotes;
	char	*closing_quote;

	i = 0;
	j = 0;
	if (with_quotes == NULL)
		return (NULL);
	without_quotes = ft_calloc(ft_strlen(with_quotes) + 1, sizeof(char));
	while (without_quotes != NULL && with_quotes[i] != '\0')
	{
		closing_quote = skip_to_closing_quote(&with_quotes[i]);
		if (!exist_closing_quote(&with_quotes[i], closing_quote))
			without_quotes[j++] = with_quotes[i++];
		else
		{
			len_of_content = set_content_of_quotations
				(&with_quotes[i], closing_quote, &without_quotes[j]);
			i += len_of_content + 2;
			j += len_of_content;
		}
	}
	return (without_quotes);
}

char	*remove_quotes_if_needed(char *env_expanded, int expand_mode)
{
	char	*without_quotes;

	if (expand_mode == FOR_HEREDOC)
		return (env_expanded);
	else
	{
		without_quotes = (remove_quotes(env_expanded));
		free (env_expanded);
		return (without_quotes);
	}
}

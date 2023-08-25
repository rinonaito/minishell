/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_remove_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:37:12 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/25 08:51:47 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *with_quotes)
{
	size_t	i;
	size_t	j;
	char	*sin_quotes;
	char	*closing_quote;

	i = 0;
	j = 0;
	if (with_quotes == NULL)
		return (NULL);
	sin_quotes = ft_calloc(ft_strlen(with_quotes) + 1, sizeof(char));
	while (with_quotes[i] != '\0')
	{
		closing_quote = skip_to_closing_quote(&with_quotes[i]);
		//対で存在する場合
		if (closing_quote == NULL || closing_quote == &with_quotes[i])
			sin_quotes[j++] = with_quotes[i++];
		//単体の場合（クオートと認識しない）
		else
		{
			i++;
			while (&with_quotes[i] != closing_quote && with_quotes[i] != '\n')
				sin_quotes[j++] = with_quotes[i++];
			i++;
		}
	}
	return (sin_quotes);
}


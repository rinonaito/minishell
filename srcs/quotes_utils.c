/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:14:51 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/25 19:06:05 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_opening_quote(char to_be_checked)
{
	if (to_be_checked == '\'' || to_be_checked == '\"')
		return (true);
	else
		return (false);
}

char	*skip_to_closing_quote(char *to_be_checked)
{
	char	*closing_quote;

	closing_quote = NULL;
	if (to_be_checked == NULL)
		return (NULL);
	if (is_opening_quote(*to_be_checked))
	{
		closing_quote = ft_strchr(to_be_checked + 1, *to_be_checked);
		return (closing_quote);
	}
	return (to_be_checked);
}

char	*find_quote(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:14:51 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/23 13:19:44 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_to_closing_quote(char *old_start)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:31:20 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/23 12:49:16 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_skip_to_closing_quote(char *old_start)
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


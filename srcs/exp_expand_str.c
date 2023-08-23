/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:37:50 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/23 14:23:45 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_quotes(char *old_start)
{
	char	*new_start;

	if (*old_start == '\'')
	{
		new_start = skip_to_closing_quote(old_start);
		if (new_start != NULL)
			return (new_start);
	}
	return (old_start);
}

char	*ft_expand_str(char *old_token, int status, t_env *env_lst)
{
	char		*new_start;
	char		*env_expanded;
	int			i;

	env_expanded = NULL;
	i = 0;
	while (old_token[i] != '\0')
	{
		new_start = check_quotes(&old_token[i]);
		i += new_start - &old_token[i];
		if (old_token[i] == '$')
		{
			env_expanded = replace_key_with_val(&old_token, &old_token[i], status, env_lst);
			if (env_expanded != NULL)
				i = -1;
		}
		i++;
	}
	if (env_expanded == NULL)
		env_expanded = ft_strndup(old_token, ft_strlen(old_token));
	return (env_expanded);
}


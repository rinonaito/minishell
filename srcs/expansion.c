/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:21:01 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/31 18:42:27 by rnaito           ###   ########.fr       */
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

char	*ft_delete_quotes(char *with_quotes)
{
	char	*sin_quotes;

	if (with_quotes != NULL)
	{
		sin_quotes = ft_get_token_sin_quotes(with_quotes);
		free (with_quotes);
	}
	return (sin_quotes);
}

char	*ft_check_quotes(char *old_start)
{
	char	*new_start;

	if (*old_start == '\'')
	{
		new_start = ft_skip_to_closing_quote(old_start);
		if (new_start != NULL)
			return (new_start);
	}
	return (old_start);
}

char	*ft_expand_str(char *old_token)
{
	char		*new_start;
	char		*env_expanded;
	char		*new_token;
	int			i;

	env_expanded = NULL;
	i = 0;
	while (old_token[i] != '\0')
	{
		new_start = ft_check_quotes(&old_token[i]);
		i += new_start - &old_token[i];
		if (old_token[i] == '$')
		{
			env_expanded = ft_replace_key_with_val(&old_token, &old_token[i]);
			if (env_expanded != NULL)
				i = -1;
		}
		i++;
	}
	if (env_expanded == NULL)
		env_expanded = ft_strndup(old_token, ft_strlen(old_token));
	return (env_expanded);
}

void	ft_expand_list(t_token **param)
{
	char		*old_token;
	char		*env_expanded;
	char		*new_token;
	char		*temp_token;
	t_token		*temp;

	temp = *param;
	while (*param != NULL)
	{
		old_token = (*param)->token;
		if (old_token != NULL)
			env_expanded = ft_expand_str(old_token);
		new_token = ft_delete_quotes(env_expanded);
		if (new_token != NULL)
		{
			temp_token = (*param)->token;
			(*param)->token = new_token;
			free(temp_token);
		}
		*param = (*param)->next;
	}
	*param = temp;
	return ;
}

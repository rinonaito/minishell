/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:11:52 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/10 20:44:01 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_key_of_env(char *doller)
{
	char	*start;
	char	*end;
	char	*quote;
	char	*another_doller;
	char	*env;

	if (*(doller + 1) == '{')
	{
		start = doller + 2;
		end = ft_strchr(start, '}');
	}
	else
	{
		start = doller + 1;
		end = ft_find_endoftoken(start);
		quote = ft_find_quote(start);
		another_doller = ft_strchr(start, '$');
		if (quote != NULL && quote < end)
			end = quote;
		if (another_doller != NULL && another_doller < end)
			end = another_doller;
	}
	env = ft_strndup(start, end - start);
	return (env);
}

char	*ft_check_quotes(char *old_start)
{
	char	*new_start;

	if (*old_start == '\'')
		new_start = ft_skip_to_closing_quote(old_start);
	else
		new_start = old_start;
	return (new_start);
}

char	*ft_make_new_token(char *token, char *doller, char *before, char *after)
{
	char	*new_token;
	int		len_before;
	int		len_after;
	int		len_token;

	len_before = ft_strlen(before);
	len_after = ft_strlen(after);
	len_token = ft_strlen(token);
	if (*(doller + 1) == '{')
		len_before += 2;
	new_token = malloc(len_token - len_before + len_after + 1);
	ft_strlcpy(new_token, token, doller - token + 1);
	ft_strlcat(new_token, after, len_token + len_after);
	ft_strlcat(new_token, doller + len_before + 1,
		len_token - len_before + len_after);
	return (new_token);
}

void	ft_replace_env(t_tree *root, char **old_token, char *doller)
{
	char		*env_l;
	char		*env_r;
	char		*new_token;
	char		*temp;

	env_l = ft_get_key_of_env(doller);
	if (env_l != NULL)
	{
		env_r = getenv(env_l);
		if (env_r != NULL)
		{
			new_token = ft_make_new_token(*old_token, doller, env_l, env_r);
			temp = root->param->token;
			root->param->token = new_token;
			*old_token = new_token;
			free (temp);
		}
	}
	free (env_l);
}

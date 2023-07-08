/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:11:52 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/08 18:55:51 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(char *str)
{
	size_t	i;
	char	*start;
	char	*end;
	char	*quote;
	char	*env;

	i = 1;
	if (str[i] == '{')
	{
		start = &str[i + 1];
		end = ft_strchr(start, '}');
	}
	else
	{
		start = &str[i];
		end = ft_find_endoftoken(start);
		quote = ft_find_quote(start);
		printf("quote = %p\n", quote);
		if (quote != NULL && quote < end)
			end = quote;
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

char	*ft_replace_env(char *token, char *start, char *before, char *after)
{
	char	*new_token;
	int		len_before;
	int		len_after;
	int		len_token;

	len_before = ft_strlen(before);
	len_after = ft_strlen(after);
	len_token = ft_strlen(token);
	new_token = malloc(len_token - len_before + len_after + 1);
	ft_strlcpy(new_token, before, len_before);
	ft_strlcpy(new_token, token, start - token + 1);
	ft_strlcat(new_token, after, len_token + len_after);
	ft_strlcat(new_token, start + len_before + 1, len_token - len_before + len_after);
	return(new_token); 
}

char	*ft_find_env(t_tree *root)
{
	size_t		i;
	char		*env_l;
	char		*env_r;
	char		*token;
	char		*new_start;
	char		*new_token;

	while (root->param != NULL && root->param->type != TK_PIPE)
	{
		i = 0;
		token = root->param->token;
		while (token[i] != '\0')
		{
			new_start = ft_check_quotes(&token[i]);
			i += new_start - &token[i];
			if (token[i] == '$')
			{
				env_l = ft_get_env(&token[i]);
				if (env_l != NULL)
				{
					env_r = getenv(env_l);
					if (env_r != NULL)
					{
						new_token = ft_replace_env(token, &token[i], env_l, env_r);
						printf("env_l = %s, env_r = %s\n", env_l, env_r);
						printf("new_token = %s\n", new_token);
					}
				}
			}
			i++;
		}
		root->param = root->param->next;
	}
	return (NULL);
}

void	ft_expand_env(t_tree *root)
{
	char	*env;

	if (root == NULL)
		return ;
	ft_expand_env(root->l_leaf);
	env = ft_find_env(root);
	ft_expand_env(root->r_leaf);
}

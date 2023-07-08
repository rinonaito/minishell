/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:11:52 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/08 15:22:32 by rnaito           ###   ########.fr       */
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

char	*ft_find_env(t_tree *root)
{
	size_t		i;
	char		*env_l;
	char		*env_r;
	char		*token;
	char		*new_start;

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
				env_r = getenv(env_l);
				printf("env_l = %s, env_r = %s\n", env_l, env_r);
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

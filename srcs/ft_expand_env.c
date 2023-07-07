/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:11:52 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/07 16:07:39 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(char *str, t_quotes *quotes)
{
	size_t	i;
	char	*start;
	char	*end;
	char	*env;

	i = 1;
	if (quotes->status == 2 && str[i] == '\"')
		return (NULL);
	if (str[i] == '{')
	{
		start = &str[i + 1];
		end = ft_strchr(start, '}');
	}
	else
	{
		start = &str[i];
		end = ft_find_spacetab(start);
		if (end == NULL)
			end = ft_strchr(start, '\0');
	}
	env = ft_strndup(start, end - start);
	printf("env = %s\n", env);
	return (env);
}

void	ft_initiate_quotes(t_quotes *quotes)
{
	quotes->s_quotes = 0;
	quotes->d_quotes = 0;
	quotes->status = 0;
}

void	ft_check_quotes(char c, t_quotes *quotes)
{
	if (c == '\'')
		quotes->s_quotes++;
	if (c == '\"')
		quotes->d_quotes++;
	if (quotes->s_quotes % 2 == 0 && quotes->d_quotes % 2 == 0)
		quotes->status = 0;
	else
	{
		if (quotes->s_quotes % 2 != 0)
			quotes->status = 1;
		else
			quotes->status = 2;
	}
}

char	*ft_find_env(t_tree *root)
{
	size_t	i;
	char	*env_l;
	char	*env_r;
	t_quotes	quotes;

	while (root->param != NULL && root->param->type != TK_PIPE)
	{
		i = 0;
		ft_initiate_quotes(&quotes);
		while (root->param->token[i] != '\0')	
		{
			ft_check_quotes(root->param->token[i], &quotes);
			if (quotes.status != 1 && root->param->token[i] == '$')
			{
				env_l = ft_get_env(&(root->param->token[i]), &quotes);
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

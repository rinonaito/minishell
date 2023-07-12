/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:21:01 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/12 14:18:49 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_find_env(t_tree *root)
{
	size_t		i;
	char		*old_token;
	char		*new_start;
	t_token		*temp;

	temp = root->param;
	while (root->param != NULL && root->param->type != TK_PIPE)
	{
		i = 0;
		old_token = root->param->token;
		while (old_token != NULL && old_token[i] != '\0')
		{
			new_start = ft_check_quotes(&old_token[i]);
			i += new_start - &old_token[i];
			if (old_token[i] == '$')
				ft_replace_env(root, &old_token, &old_token[i]);
			i++;
		}
		root->param = root->param->next;
	}
	root->param = temp;
}

void	ft_expand_env(t_tree *root)
{
	if (root == NULL)
		return ;
	ft_expand_env(root->l_leaf);
	ft_find_env(root);
	ft_expand_env(root->r_leaf);
}

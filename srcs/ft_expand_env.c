/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:21:01 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/14 18:14:13 by rnaito           ###   ########.fr       */
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

int	ft_find_env(t_tree *root)
{
	size_t		i;
	char		*old_token;
	char		*new_start;
	t_token		*temp;
	int			is_replaced;

	temp = root->param;
	is_replaced = 0;
	while (root->param != NULL && root->param->type != TK_PIPE)
	{
		i = 0;
		old_token = root->param->token;
		while (old_token != NULL && old_token[i] != '\0')
		{
			new_start = ft_check_quotes(&old_token[i]);
			i += new_start - &old_token[i];
			if (old_token[i] == '$')
				is_replaced = ft_replace_env(root, &old_token, &old_token[i]);
			i++;
		}
		root->param = root->param->next;
	}
	root->param = temp;
	return (is_replaced);
}

void	ft_expand_env(t_tree *root)
{
	int	is_replaced;

	if (root == NULL)
		return ;
	ft_expand_env(root->l_leaf);
	is_replaced = ft_find_env(root);
	if (is_replaced == 1)
	{
		ft_split_expanded_token(root->param);
		printf("root->param->token = %s\n", root->param->token);
	}
	ft_expand_env(root->r_leaf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:21:01 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/14 21:32:22 by rnaito           ###   ########.fr       */
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

int	ft_find_env(t_tree *root, char *old_token)
{
	char		*new_start;
	int			is_replaced;
	int			ret_val;
	size_t		i;

	is_replaced = 0;
	i = 0;
	while (old_token != NULL && old_token[i] != '\0')
	{
		if (is_replaced == 1)
		{
			i = 0;
			is_replaced = 0;
		}
		new_start = ft_check_quotes(&old_token[i]);
		i += new_start - &old_token[i];
		if (old_token[i] == '$')
		{
			is_replaced = ft_replace_env(root, &old_token, &old_token[i]);
			ret_val = is_replaced;
		}
		i++;
	}
	return (ret_val);
}

int	ft_check_all_param(t_tree *root)
{
	char		*old_token;
	t_token		*temp;
	int			ret_val;

	temp = root->param;
	while (root->param != NULL && root->param->type != TK_PIPE)
	{
		old_token = root->param->token;
		ret_val = ft_find_env(root, old_token);
		root->param = root->param->next;
	}
	root->param = temp;
	return (ret_val);
}

void	ft_expand_env(t_tree *root)
{
	int	is_replaced;

	if (root == NULL)
		return ;
	ft_expand_env(root->l_leaf);
	is_replaced = ft_check_all_param(root);
	if (is_replaced == 1)
		ft_split_expanded_token(root->param);
	ft_delete_quotes(root->param);
	ft_expand_env(root->r_leaf);
}

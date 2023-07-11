/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:21:01 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/11 13:20:10 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_quotes(char *old_start)
{
	char	*new_start;

	if (*old_start == '\'')
		new_start = ft_skip_to_closing_quote(old_start);
	else
		new_start = old_start;
	return (new_start);
}

int	ft_find_env(t_tree *root)
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
			if (new_start == NULL)
				break ;
			i += new_start - &old_token[i];
			if (old_token[i] == '$')
				if (ft_replace_env(root, &old_token, &old_token[i]) == 1)
					return (1);
			i++;
		}
		root->param = root->param->next;
	}
	root->param = temp;
	return (0);
}

int	ft_expand_env(t_tree *root)
{
	if (root == NULL)
		return (0);
	ft_expand_env(root->l_leaf);
	if (ft_find_env(root) == 1)
		return (1);
	ft_expand_env(root->r_leaf);
	return (0);
}

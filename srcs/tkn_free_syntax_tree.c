/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_free_syntax_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:42:38 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/10 16:07:36 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tree_itself(t_tree *root)
{
	if (root == NULL)
		return ;
	free_tree_itself(root->l_leaf);
	free_tree_itself(root->r_leaf);
	free(root);
	root = NULL;
}

void	free_syntax_tree(t_tree *root, t_token *head)
{
	ft_lstclear_token(&head);
	free_tree_itself(root);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_make_syntax_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:42:38 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/01 16:15:24 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tree	*make_node(t_token **token)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (new_node == NULL)
		ft_perror("malloc");
	new_node->type = TK_PIPE;
	new_node->param = NULL;
	new_node->r_leaf = NULL;
	new_node->l_leaf = NULL;
	if (*token != NULL)
		(*token) = (*token)->next;
	return (new_node);
}

static void	complete_node(t_tree **node, t_tree *right, t_tree *left)
{
	if (*node == NULL)
		return ;
	(*node)->r_leaf = right;
	(*node)->l_leaf = left;
}

static t_tree	*make_leaf(t_token **token)
{
	t_tree	*new_leaf;

	if (*token == NULL)
		return (NULL);
	new_leaf = malloc(sizeof(t_tree));
	if (new_leaf == NULL)
		ft_perror("malloc");
	new_leaf->type = TK_WORD;
	new_leaf->param = *token;
	new_leaf->r_leaf = NULL;
	new_leaf->l_leaf = NULL;
	while ((*token) != NULL && (*token)->type != TK_PIPE)
		(*token) = (*token)->next;
	return (new_leaf);
}

t_tree	*make_syntax_tree(t_token *token)
{
	t_tree	*node;
	t_tree	*right;
	t_tree	*left;
	int		num_of_pipe;

	node = NULL;
	left = make_leaf(&token);
	num_of_pipe = 0;
	while (token != NULL)
	{
		if (token->type == TK_PIPE)
		{
			num_of_pipe++;
			node = make_node(&token);
		}
		if (token != NULL && token->type != TK_PIPE)
			right = make_leaf(&token);
		if ((node == NULL && num_of_pipe != 0) || right == NULL)
			return (NULL);
		complete_node(&node, right, left);
		left = node;
	}
	if (num_of_pipe == 0)
		return (left);
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_syntax_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:42:38 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/07 20:06:55 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//@func: allocate memory for the node in syntax tree and
//initiate with type "TK_PIPE"
//@param:
//	t_token *token: token with the type "TK_PIPE"
//@return_val: pionter of the new node 
t_tree	*ft_make_node(t_token **token)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	new_node->type = TK_PIPE;
	new_node->r_leaf = NULL;
	new_node->l_leaf = NULL;
	if (*token != NULL)
		(*token) = (*token)->next;
	return (new_node);
}

//@func: put the pointer of right and left leaf in a node
//@param:
//	t_tree *node: pointer of the node to complete
//	t_tree *right: pointer of the right leaf
//	t_tree *left: pointer of the left leaf
//@return_val: pointer of the completed node
void	ft_complete_node(t_tree **node, t_tree *right, t_tree *left)
{
	if (*node == NULL)
		return ;
	(*node)->r_leaf = right;
	(*node)->l_leaf = left;
}

//@func: find command string in the list of token and return the string 
//@param:
//	t_token *token: head of the list token
//@return_val: string of command
char	*ft_find_command(t_token *token)
{
	while (token != NULL && token->type != TK_PIPE)
	{
		if (token->type == TK_WORD)
			return (token->token);
		if (token->type >= TK_REDIR_IN && token->type <= TK_HEREDOC)
			token = token->next;
		if (token != NULL)
			token = token->next;
	}
	return (NULL);
}

//@func: allocate memory for the leaf in tree struct and
//initiate with type "TK_PIPE"
//@param: pointer of the token with the type non"TK_PIPE"
//@return_val: pointer of the new leaf
t_tree	*ft_make_leaf(t_token **token)
{
	t_tree	*new_leaf;

	if (*token == NULL)
		return (NULL);
	new_leaf = malloc(sizeof(t_tree));
	new_leaf->type = TK_WORD;
	new_leaf->command = ft_find_command(*token);
	new_leaf->param = *token;
	new_leaf->r_leaf = NULL;
	new_leaf->l_leaf = NULL;
	while ((*token) != NULL && (*token)->type != TK_PIPE)
		(*token) = (*token)->next;
	return (new_leaf);
}

//@func: make a syntax tree from the list of token
//@param: 
//	t_token *head: head of the token list
//@return_val: pointer of the top of syntax tree
t_tree	*ft_make_syntax_tree(t_token *token)
{
	t_tree	*node;
	t_tree	*right;
	t_tree	*left;

	node = NULL;
	left = ft_make_leaf(&token);
	while (token != NULL)
	{
		if (token->type == TK_PIPE)
			node = ft_make_node(&token);
		if (token != NULL && token->type != TK_PIPE)
			right = ft_make_leaf(&token);
		ft_complete_node(&node, right, left);
		left = node;
	}
	if (node == NULL)
		return (left);
	return (node);
}

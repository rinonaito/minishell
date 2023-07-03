/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_syntax_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:42:38 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/03 21:42:39 by rnaito           ###   ########.fr       */
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
	if (*token != NULL)
		(*token) = (*token)->next;
	return (new_node);
}

//@func: put the pointer of right and left branch in a node
//@param:
//	t_tree *node: pointer of the node to complete
//	t_tree *right: pointer of the right branch
//	t_tree *left: pointer of the left branch
//@return_val: pointer of the completed node
void	ft_complete_node(t_tree **node, t_tree *right, t_tree *left)
{
	if (*node == NULL)
		return ;
	(*node)->r_branch = right;
	(*node)->l_branch = left;
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
		token = token->next;
	}
	return (NULL);
}

//@func: allocate memory for the branch in tree struct and
//initiate with type "TK_PIPE"
//@param: pointer of the token with the type non"TK_PIPE"
//@return_val: pointer of the new branch
t_tree	*ft_make_branch(t_token **token)
{
	t_tree	*new_branch;

	if (*token == NULL)
		return (NULL);
	new_branch = malloc(sizeof(t_tree));
	new_branch->type = TK_WORD;
	new_branch->command = ft_find_command(*token);
	new_branch->param = (*token);
	while ((*token) != NULL && (*token)->type != TK_PIPE)
		(*token) = (*token)->next;
	return (new_branch);
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
	left = ft_make_branch(&token);
	while (token != NULL)
	{
		if (token->type == TK_PIPE)
			node = ft_make_node(&token);
		if (token->type != TK_PIPE)
			right = ft_make_branch(&token);
		ft_complete_node(&node, right, left);
		left = node;
	}
	if (node == NULL)
		return (left);
	return (node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/06/30 14:11:59 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//@func: return the type of the token (as int) accorging to the parameter
//@param:
//	char *token: string of the token to be judged
//@return_val: type(TK_WORD or TK_OPERATOR) of the token

/*
int	ft_check_token_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (TK_OPERATOR);
//	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0)
//		return (TK_OPERATOR);
//	if (ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0)
//		return (TK_OPERATOR);
	return (TK_WORD);
}
*/

//@func: make a list of struct t_token 
//@param:
//	char *line: a string of input
//@return_val: pointer of the head node of the list
/*
t_token	*ft_tokenize(char *line)
{	
	char	*token;
	t_token	*head;
	t_token	*new;
	int		type;

	if (line != NULL)
		head = ft_lstnew_ms(NULL, 0);
	while (line != NULL)
	{
		token = ft_get_token(&line);
		type = ft_check_token_type(token);
		new = ft_lstnew_ms(token, type);
		ft_lstadd_back_ms(&head, new);
	}
	return (head);
}
*/

//@dscr: create a new node for a tree structure
//@parm:
//	char *token: word to be copied
//	t_token_type type: type of the token
//	t_tree *left: the node to be copied to the left
//	t_tree *right: the node to be copied to the right
t_tree *new_node(char *token, t_token_type type, t_tree *left, t_tree *right)
{
  t_tree *node;
 
  node = malloc(sizeof(t_tree));

  node->token = token;
  node->type = type;
  node->left = left;
  node->right = right;
  return (node);
}

t_tree	parser(t_token *list)
{
	t_token	*head_token;
	t_tree	*tree;
	t_tree	*head_tree;
	//t_token	*new;
	int		type;

	if (!list)
		return (NULL);
	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	/*
	head_tree = tree;
	head_tree->right = NULL;
	head_tree->left = NULL;
	*/
	while (list)
	{
		tree->token = NULL;
		if (list->token)
			tree->token = list->token;
		//if (token->type = TK_OPERATOR)
			

		token = token->next;
	}

	return (head);
}


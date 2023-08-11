/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/11 16:05:42 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//@func: return the type of the token (as int) accorging to the parameter
//@param:
//	char *token: string of the token to be judged
//@return_val: type(TK_WORD or TK_OPERATOR) of the token
int	ft_check_token_type(char *token)
{
	if (ft_strequ(token, "|"))
		return (TK_PIPE);
	if (ft_strequ(token, "<"))
		return (TK_REDIR_IN);
	if (ft_strequ(token, ">"))
		return (TK_REDIR_OUT);
	if (ft_strequ(token, "<<"))
		return (TK_HEREDOC);
	if (ft_strequ(token, ">>"))
		return (TK_APPEND);
	return (TK_WORD);
}

//@func: make a node for the param token and
//put it at the end of the list.
//@param:
//	t_token	**param: pointer of the head of the list
//	char	*token: string of the token
int	ft_put_token_inlist(t_token **head, char *token)
{
	t_token	*new;
	int		type;
	int		is_heredoc;

	is_heredoc = 0;
	type = ft_check_token_type(token);
	if (type == TK_HEREDOC)
		is_heredoc = 1;
	new = ft_lstnew_token(token, type);
	ft_lstadd_back_token(head, new);
	return (is_heredoc);
}


//@func: tokenize the input
//@param:
//	char *line: a string of input
//@return_val: head node of the token list
t_token	*ft_tokenize(char *line, int *status)
{	
	t_token	*head;
	int		is_heredoc;

	if (ft_strlen(line) == 0)
		return (NULL);
	if (line != NULL)
		head = ft_lstnew_token(NULL, 0);
	is_heredoc = make_token_list(&head, line);
	if (ft_is_syntax_error(head) == 1)
	{
		*status = SYNTAX_ERR;
		ft_lstclear_token(&head);
	}
	if (is_heredoc == 1 && *status != SYNTAX_ERR)
		*status = HEREDOC_MODE;
	return (head);
}

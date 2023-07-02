/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/02 17:06:48 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//@func: return the type of the token (as int) accorging to the parameter
//@param:
//	char *token: string of the token to be judged
//@return_val: type(TK_WORD or TK_OPERATOR) of the token
int	ft_check_token_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (TK_PIPE);
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0)
		return (TK_REDIR);
	if (ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0)
		return (TK_REDIR);
	return (TK_WORD);
}

//@func: make a list of struct t_token 
//@param:
//	char *line: a string of input
//@return_val: pointer of the head node of the list
t_token	*ft_tokenize(char *line)
{	
	char	*token;
	t_token	*head;
	t_token	*new;
	int		type;
	int		not_closed;

	if (line != NULL)
		head = ft_lstnew_ms(NULL, TK_HEAD);
	not_closed = 0;
	while (line != NULL)
	{
		token = ft_get_token(&line, &not_closed);
		if (token != NULL)
		{
			type = ft_check_token_type(token);
			new = ft_lstnew_ms(token, type);
			ft_lstadd_back_ms(&head, new);
		}
	}
	if (not_closed == 1 || ft_is_syntaxerror(head) == 1)
	{
		printf("syntax error\n");
		ft_lstclear_ms(&head);
	}
	return (head);
}

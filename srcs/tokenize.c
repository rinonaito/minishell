/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/07 16:02:34 by rnaito           ###   ########.fr       */
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
	if (ft_strcmp(token, "<") == 0)
		return (TK_REDIR_IN);
	if (ft_strcmp(token, ">") == 0)
		return (TK_REDIR_OUT);
	if (ft_strcmp(token, "<<") == 0)
		return (TK_HEREDOC);
	if (ft_strcmp(token, ">>") == 0)
		return (TK_APPEND);
	return (TK_WORD);
}

//@func: make the list of token 
//@param:
//	t_token **head: head node of the list
//	char	*line: input string
//@return_val: return 0 if there is NO quotation error
//	return 1 if the quotation is not closed
int	ft_make_token_list(t_token **head, char *line)
{
	char	*token;
	t_token	*new;
	int		type;
	int		not_closed;

	not_closed = 0;
	while (line != NULL)
	{
		token = ft_get_token(&line);
		printf("token = %s\n", token);
		if (token == NULL)
		{
			not_closed = 1;
			break ;
		}
		else
		{
			type = ft_check_token_type(token);
			new = ft_lstnew_ms(token, type);
			ft_lstadd_back_ms(head, new);
		}
	}
	if ((*head)->next != NULL)
	{
		(*head)->next->prev = NULL;
		(*head) = (*head)->next;
	}
	return (not_closed);
}

//@func: tokenize the input
//@param:
//	char *line: a string of input
//@return_val: head node of the token list
t_token	*ft_tokenize(char *line)
{	
	t_token	*head;
	int		not_closed;

	if (ft_strlen(line) == 0)
		return (NULL);
	if (line != NULL)
		head = ft_lstnew_ms(NULL, 0);
	not_closed = ft_make_token_list(&head, line);
	if (not_closed == 1 || ft_is_syntax_error(head) == 1)
	{
		printf("syntax error\n");
		ft_lstclear_ms(&head);
	}
	return (head);
}

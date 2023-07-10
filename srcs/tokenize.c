/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/10 18:14:22 by rnaito           ###   ########.fr       */
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

//@func: make a node for the param token and
//put it at the end of the list.
//@param:
//	t_token	**param: pointer of the head of the list
//	char	*token: string of the token
void	ft_put_token_inlist(t_token **head, char *token)
{
	t_token	*new;
	int		type;

	type = ft_check_token_type(token);
	new = ft_lstnew_ms(token, type);
	ft_lstadd_back_ms(head, new);
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
	int		not_closed;
	t_token	*temp;

	not_closed = 0;
	while (ft_strlen(line) != 0)
	{
		token = ft_get_token(&line, &not_closed);
		if (token == NULL)
			break ;
		else
			ft_put_token_inlist(head, token);
	}
	temp = *head;
	if ((*head)->next != NULL)
	{
		(*head)->next->prev = NULL;
		(*head) = (*head)->next;
	}
	else
		(*head) = NULL;
	free (temp);
	return (not_closed);
}

//@func: tokenize the input
//@param:
//	char *line: a string of input
//@return_val: head node of the token list
t_token	*ft_tokenize(char *line, int *is_error)
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
		*is_error = 1;
		ft_lstclear_ms(&head);
	}
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/19 16:17:38 by rnaito           ###   ########.fr       */
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
int	ft_put_token_inlist(t_token **head, char *token)
{
	t_token	*new;
	int		type;
	int		is_heredoc;

	is_heredoc = 0;
	type = ft_check_token_type(token);
	if (type == TK_HEREDOC)
		is_heredoc = 1;
	new = ft_lstnew_ms(token, type);
	ft_lstadd_back_ms(head, new);
	return (is_heredoc);
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
	t_token	*temp;
	int		is_heredoc;

	is_heredoc = 0;
	while (ft_strlen(line) != 0)
	{
		token = ft_get_token(&line);
		if (token == NULL)
			break ;
		else
		{
			if (ft_put_token_inlist(head, token) == 1)
				is_heredoc = 1;
		}
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
		head = ft_lstnew_ms(NULL, 0);
	is_heredoc = ft_make_token_list(&head, line);
	if (ft_is_syntax_error(head) == 1)
	{
		*status = SYNTAX_ERR;
		ft_lstclear_ms(&head);
	}
	if (is_heredoc == 1)
		*status = HEREDOC_MODE;
	return (head);
}

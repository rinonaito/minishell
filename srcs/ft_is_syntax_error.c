/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:50:57 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/03 21:51:05 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//@func: check if there is syntax error 
//@param:
//	t_token *head: head of the list t_token
//@return_val: return 1 if there is syntax error. 
// return 0 if the syntax is correct.
int	ft_is_syntax_error(t_token *head)
{
	t_token	*token;

	token = head->next;
	while (token != NULL)
	{
		if (token->type == TK_PIPE)
		{
			if (token->prev->type != TK_WORD)
				return (1);
			if (token->next == NULL || token->next->type == TK_PIPE)
				return (1);
		}
		if (token->type >= TK_REDIR_IN && token->type <= TK_HEREDOC)
		{
			if (token->next == NULL || token->next->type != TK_WORD
				|| *(token->next->token) == '\0')
				return (1);
		}
		token = token->next;
	}
	return (0);
}

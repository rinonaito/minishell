/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/27 20:59:59 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_syntax_error(t_token *head)
{
	while (head != NULL)
	{
		if (head->type == TK_PIPE)
		{
			if (head->prev == NULL || head->next == NULL)
				return (1);
			if (head->prev->type != TK_WORD)
				return (1);
			if (head->next->type == TK_PIPE)
				return (1);
		}
		if (head->type >= TK_REDIR_IN && head->type <= TK_HEREDOC)
		{
			if (head->next == NULL)
				return (1);
			if (head->next->type != TK_WORD)
				return (1);
			if (*(head->next->token) == '\0')
				return (1);
		}
		head = head->next;
	}
	return (0);
}

t_token	*tokenize(char *line, int *status)
{	
	t_token	*head;
	int		have_heredoc;

	if (line == NULL || ft_strlen(line) == 0)
		return (NULL);
	head = make_token_list(line, &have_heredoc);
	if (head != NULL)
	{
		if (is_syntax_error(head) == 1)
		{
			*status = SYNTAX_ERR;
			ft_lstclear_token(&head);
		}
		if (have_heredoc == 1 && *status != SYNTAX_ERR)
			*status = HEREDOC_MODE;
	}
	return (head);
}

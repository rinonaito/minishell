/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/11 18:34:56 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_type(char *token)
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

int	is_syntax_error(t_token *head)
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
	if (is_syntax_error(head) == 1)
	{
		*status = SYNTAX_ERR;
		ft_lstclear_token(&head);
	}
	if (have_heredoc == 1 && *status != SYNTAX_ERR)
		*status = HEREDOC_MODE;
	return (head);
}

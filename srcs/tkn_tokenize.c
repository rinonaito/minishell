/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/01 14:12:26 by rnaito           ###   ########.fr       */
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

t_token	*tokenize(char *line, int *have_heredoc, int *status)
{	
	t_token	*head;

	if (ft_strlen(line) == 0)
		return (NULL);
	head = make_token_list(line, have_heredoc);
	if (head == NULL)
		exit(1);
	if (ft_strlen(head->token) == 0)
	{
		*status = 0;
		free(head->token);
		free(head);
		return (NULL);
	}
	if (is_syntax_error(head) == 1)
	{
		ft_printf_fd(2, "bash: syntax error:\n");
		*status = 258;
		return (NULL);
	}
	return (head);
}

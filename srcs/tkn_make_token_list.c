/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_make_token_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:53:40 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/01 15:48:39 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*make_node_for_token(char *token, int	*have_heredoc)
{
	int		token_type;
	t_token	*new;

	token_type = get_token_type(token);
	if (token_type == TK_HEREDOC)
		*have_heredoc = 1;
	new = ft_lstnew_token(token, token_type);
	if (new == NULL)
		ft_perror("malloc");
	return (new);
}

t_token	*make_token_list(char *line, int *have_heredoc)
{
	char	*token;
	t_token	*head;
	t_token	*new;

	*have_heredoc = 0;
	head = NULL;
	while (ft_strlen(line) != 0)
	{
		token = get_token(&line);
		new = make_node_for_token(token, have_heredoc);
		ft_lstadd_back_token(&head, new);
	}
	return (head);
}

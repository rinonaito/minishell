/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:53:40 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/23 11:50:40 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*make_token_list(char *line, int *have_heredoc)
{
	char	*token;
	t_token	*head;
	t_token	*new;
	int		token_type;

	*have_heredoc = 0;
	head = NULL;
	while (ft_strlen(line) != 0)
	{
		token = ft_get_token(&line);
		if (token == NULL)
			break ;
		else
		{
			token_type = get_token_type(token);
			new = ft_lstnew_token(token, token_type);
			ft_lstadd_back_token(&head, new);
			if (token_type == TK_HEREDOC)
				*have_heredoc = 1;
		}
	}
	return (head);
}

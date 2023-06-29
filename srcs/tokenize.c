/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:03:35 by rnaito            #+#    #+#             */
/*   Updated: 2023/06/29 13:50:11 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_token_type(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (TK_OPERATOR);
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0)
		return (TK_OPERATOR);
	if (ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0)
		return (TK_OPERATOR);
	return (TK_WORD);
}

t_token	*ft_tokenize(char *line)
{	
	char	*token;
	t_token	*head;
	t_token	*new;
	int		type;

	if (line != NULL)
		head = ft_lstnew_ms(NULL, 0);
	while (line != NULL)
	{
		token = ft_get_token(&line);
		type = ft_check_token_type(token);
		new = ft_lstnew_ms(token, type);
		ft_lstadd_back_ms(&head, new);
	}
	return (head);
}

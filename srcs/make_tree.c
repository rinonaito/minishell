/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:48:40 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/02 20:52:32 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_get_tree_size(t_token *head)
{
	t_token *token;
	size_t	size;

	token = head->next;
	size = 1;
	while (token != NULL)
	{
		if (token->type == TK_PIPE)
			size += 2;
		token = token->next;
	}
	return (size);
}

t_tree	*make_tree(t_token *head)
{
	size_t	size;
	size_t	i;
	t_tree	*tree_head;
	
	size = ft_get_tree_size(head);
	i = 0;
	while (i < size)
	{
		
	}
	

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:37:34 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/01 19:07:51 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_ms(char *token, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->token = token;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast_ms(t_token *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

void	ft_lstadd_back_ms(t_token **head, t_token *new)
{
	t_token	*tail;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tail = ft_lstlast_ms(*head);
	tail->next = new;
}

void	ft_lstdel(t_token **current_node)
{
	(*current_node)->token = NULL;
	(*current_node)->type = 0;
	(*current_node)->next = NULL;
}

void	ft_lstclear_ms(t_token **head)
{
	t_token	*current_node;
	t_token	*temp;

	if (head == NULL)
		return ;
	current_node = *head;
	while (current_node->next != NULL)
	{				
		temp = current_node->next;
		ft_lstdel(&current_node);
		free(current_node);
		current_node = temp;
	}
	*head = NULL;
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:53:40 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/11 16:11:04 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_token(char *token, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->token = token;
	new->type = type;
	new->heredoc = NULL;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast_token(t_token *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

void	ft_lstadd_back_token(t_token **head, t_token *new)
{
	t_token	*tail;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tail = ft_lstlast_token(*head);
	tail->next = new;
	new->prev = tail;
}

void	ft_lstclear_token(t_token **head)
{
	t_token	*current_node;
	t_token	*temp;

	if (head == NULL || *head == NULL)
		return ;
	current_node = *head;
	while (current_node->next != NULL)
	{				
		temp = current_node->next;
		free(current_node->token);
		current_node->token = NULL;
		current_node->type = 0;
		free(current_node);
		current_node = temp;
	}
	free(current_node);
	*head = NULL;
	return ;
}

int	make_token_list(t_token **head, char *line)
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

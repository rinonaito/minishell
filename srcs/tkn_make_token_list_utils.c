/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_make_token_list_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:44:51 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/28 21:37:52 by rnaito           ###   ########.fr       */
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
	new->prev = NULL;
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
	while (current_node != NULL)
	{				
		temp = current_node->next;
		free(current_node->token);
		current_node->token = NULL;
		free(current_node->heredoc);
		current_node->heredoc = NULL;
		current_node->type = 0;
		free(current_node);
		current_node = temp;
	}
	free(current_node);
	*head = NULL;
	head = NULL;
	return ;
}

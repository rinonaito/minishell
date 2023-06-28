/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:14:00 by rnaito            #+#    #+#             */
/*   Updated: 2023/06/28 17:17:46 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_ms(char *token, int	type)
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
	t_token *tail;
	
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tail = ft_lstlast_ms(*head);
	tail->next = new;
}

char	*ft_strndup(char *str, size_t len)
{
	char	*new;
	size_t	i;

	new = malloc(sizeof(char) * len + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strchrchr(char *str, char c1, char c2)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c1 || str[i] == c2)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

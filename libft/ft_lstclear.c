/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:58:59 by rnaito            #+#    #+#             */
/*   Updated: 2023/04/10 15:00:30 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_node;
	t_list	*temp;

	if (lst == NULL || del == NULL || *lst == NULL)
		return ;
	current_node = *lst;
	while (current_node != NULL)
	{
		temp = current_node->next;
		del(current_node->content);
		free(current_node);
		current_node = temp;
	}
	*lst = NULL;
}

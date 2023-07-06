/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:04:50 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/05 08:21:07 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new || !lst)
		return ;
	temp = *lst;
	*lst = new;
	(*lst)->next = temp;
}

/*
int main(void)
{
	char	str[] = "hello";
	t_list *lst;
	t_list *lst_temp;
	t_list *lst1;
	t_list *lst2;
	t_list *lst3;
	t_list *lst4;

	lst1 = malloc(sizeof(t_list));
	lst2 = malloc(sizeof(t_list));
	lst3 = malloc(sizeof(t_list));
	lst4 = malloc(sizeof(t_list));

	lst1->content = str;
	lst2->content = str;
	lst3->content = str;
	lst4->content = "world";

	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = NULL;

	lst = lst1;
	lst_temp = lst1;
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	//ft_lstadd_front(lst_temp, lst4);
	ft_lstadd_front(&lst_temp, lst4);
	while (lst_temp)
	{
		printf("%s\n", (char *)lst_temp->content);
		lst_temp = lst_temp->next;
	}
	return (0);
}
*/

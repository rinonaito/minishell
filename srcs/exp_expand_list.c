/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:41:43 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/28 21:01:45 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_list(t_token **head, int exit_status, t_env *env_lst)
{
	char		*to_be_expanded;
	char		*expanded;
	t_token		*temp;

	printf("*head->token = %s\n", (*head)->token);
	temp = *head;
	while (*head != NULL)
	{
		to_be_expanded = (*head)->token;
		if (to_be_expanded != NULL)
		{
			expanded = ft_expand_str(to_be_expanded, exit_status,
					env_lst, FOR_NORMAL);
			if (expanded == NULL)
			{
				printf("expanded = NULL\n");
				return (1);
			}
			(*head)->token = expanded;
		}
		*head = (*head)->next;
	}
	*head = temp;
	printf("*head->token = %s\n", (*head)->token);
	return (0);
}

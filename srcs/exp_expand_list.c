/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:41:43 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/31 19:07:10 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_list(t_token **head, int exit_status, t_env *env_lst)
{
	char		*to_be_expanded;
	char		*expanded;
	t_token		*temp;
	int		ret;

	temp = *head;
	ret = 0;
	while (*head != NULL)
	{
		to_be_expanded = (*head)->token;
		if (to_be_expanded != NULL)
		{
			expanded = expand_str(to_be_expanded, exit_status,
					env_lst, FOR_NORMAL);
			if (expanded == NULL)
				ret = 1;
			else
				(*head)->token = expanded;
		}
		*head = (*head)->next;
	}
	*head = temp;
	return (ret);
}

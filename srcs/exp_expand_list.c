/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:41:43 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/25 10:23:47 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_list(t_token **head, int status, t_env *env_lst)
{
	char		*to_be_expanded;
	char		*expanded;
	char		*temp_token;
	t_token		*temp;

	temp = *head;
	while (*head != NULL)
	{
		to_be_expanded = (*head)->token;
		expanded = ft_expand_str(to_be_expanded, status, env_lst, false);
		temp_token = (*head)->token;
		(*head)->token = expanded;
		free(temp_token);
		*head = (*head)->next;
	}
	*head = temp;
	return ;
}

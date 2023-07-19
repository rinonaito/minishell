/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:41:26 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/19 17:50:59 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_env *head)
{
	while (head != NULL)
	{
		printf("%s=%s\n", head->key, head->val);
		head = head->next;
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:41:26 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/06 18:54:10 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_cmds *cmds_info)
{
	t_env	*tmp;
	t_env	*head;

	head = cmds_info->env_lst;
	tmp = head;
	printf("head = %p\n", head);
	while (head != NULL)
	{
		printf("%s=%s\n", head->key, head->val);
		head = head->next;
	}
	cmds_info->env_lst = tmp;
	return (0);
}

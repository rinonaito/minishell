/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:41:26 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/09 12:09:30 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_cmds *cmds_info)
{
	t_env	*tmp;
	t_env	*head;

	head = cmds_info->env_lst;
	tmp = head;
	while (head != NULL)
	{
		if (head->val != NULL)
			printf("%s=%s\n", head->key, head->val);
		head = head->next;
	}
	cmds_info->env_lst = tmp;
	return (0);
}

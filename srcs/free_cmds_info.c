/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:48:18 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/06 20:10:48 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env_lst(t_env **lst)
{
	t_env	*current_node;
	t_env	*temp;

	if (lst == NULL || *lst == NULL)
		return ;
	current_node = *lst;
	while (current_node != NULL)
	{
		temp = current_node->next;
		free(current_node->key);
		free(current_node->val);
		free(current_node);
		current_node = temp;
	}
	*lst = NULL;
}

void	free_cmds_info(t_cmds *cmds_info)
{
	free(cmds_info->pid_ary);
	clear_env_lst(&(cmds_info->env_lst));	
}

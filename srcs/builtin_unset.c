/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:01:07 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/10 14:06:19 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone_env(t_env *env_lst, t_env *node)
{
	t_env	*tmp;

	tmp = env_lst;
	while (env_lst->next != node)
	{
		env_lst = env_lst->next;
	}
	env_lst->next = node->next;
	free (node->key);
	node->key = NULL;
	free (node->val);
	node->val = NULL;
	node->next = NULL;
	free(node);
	env_lst = tmp;
}

int	builtin_unset(t_cmds *cmds_info)
{
	size_t	i;
	char	*key;
	t_env	*same_key_node;

	if (cmds_info->cmd_args[1] == NULL)
		return (0);
	i = 1;
	while ((cmds_info->cmd_args[i] != NULL))
	{
		key = cmds_info->cmd_args[i];
		same_key_node = search_same_key(cmds_info->env_lst, key);
		if (same_key_node != NULL)
			ft_lstdelone_env(cmds_info->env_lst, same_key_node);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:01:07 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/04 17:22:10 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lstdelone_env(t_env **env_lst, t_env *node)
{
	t_env	*tmp;

	if (*env_lst == node)
		tmp = (*env_lst)->next;
	else
	{
		tmp = *env_lst;
		while ((*env_lst)->next != node)
			*env_lst = (*env_lst)->next;
		(*env_lst)->next = node->next;
	}
	free (node->key);
	node->key = NULL;
	free (node->val);
	node->val = NULL;
	node->next = NULL;
	free(node);
	*env_lst = tmp;
}

static void	for_wrong_key(t_cmds *cmds_info, int i, int *ret)
{
	ft_printf_fd(2, "minishell: %s: `%s': not a valid identifier\n",
		cmds_info->cmd_args[0], cmds_info->cmd_args[i]);
	*ret = 1;
}

int	builtin_unset(t_cmds *cmds_info)
{
	size_t	i;
	char	*key;
	t_env	*same_key_node;
	int		ret;

	ret = 0;
	if (cmds_info->cmd_args[1] == NULL)
		return (ret);
	i = 1;
	while ((cmds_info->cmd_args[i] != NULL))
	{
		key = cmds_info->cmd_args[i];
		if (is_wrong_key_name(key) == 1)
			for_wrong_key(cmds_info, i, &ret);
		else
		{
			same_key_node = search_same_key(cmds_info->env_lst, key);
			if (same_key_node != NULL)
				ft_lstdelone_env(&(cmds_info->env_lst), same_key_node);
		}
		i++;
	}
	return (ret);
}

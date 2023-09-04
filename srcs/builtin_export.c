/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:18:14 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/04 17:07:17 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_env(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (head != NULL)
	{
		printf("declare -x %s", head->key);
		if (head->val != NULL)
			printf("=\"%s\"", head->val);
		printf("\n");
		head = head->next;
	}
	head = tmp;
	return (0);
}

void	change_val(t_env *same_key_node, char *val)
{
	if (val == NULL)
		return ;
	free(same_key_node->val);
	same_key_node->val = val;
	return ;
}

static void	change_env_list(t_env *same_key_node, t_env **env_list, char *key,
		char *val)
{
	if (same_key_node == NULL)
		ft_lstadd_back_env(env_list, ft_lstnew_env(key, val));
	else
	{
		change_val(same_key_node, val);
		free (key);
	}
}

static void	for_wrong_key(t_cmds *cmds_info, int i, int *ret, char *key)
{
	ft_printf_fd(2, "minishell: %s: `%s': not a valid identifier\n",
		cmds_info->cmd_args[0], cmds_info->cmd_args[i]);
	free(key);
	*ret = 1;
}

int	builtin_export(t_cmds *cmds_info)
{
	char	*key;
	char	*val;
	t_env	*same_key_node;
	size_t	i;
	int		ret;

	if (cmds_info->cmd_args[1] == NULL)
		return (print_env(cmds_info->env_lst));
	ret = 0;
	i = 1;
	while ((cmds_info->cmd_args)[i] != NULL)
	{
		key = get_key_for_env_list(cmds_info->cmd_args[i], &val);
		if (is_wrong_key_name(key) == 1)
			for_wrong_key(cmds_info, i, &ret, key);
		else
		{
			val = get_val_for_env_list(val);
			same_key_node = search_same_key(cmds_info->env_lst, key);
			change_env_list(same_key_node, &(cmds_info->env_lst), key, val);
		}
		i++;
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:18:14 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/11 15:07:19 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_val(t_env *same_key_node, char *val)
{
	size_t	i;
	char	*new_val;

	if (val == NULL)
		return ;
	free(same_key_node->val);
	same_key_node->val = NULL;
	new_val = malloc(sizeof(char) * ft_strlen(new_val) + 1);
	i = 0;
	while (val[i] != '\0')
	{
		new_val[i] = val[i];
		i++;
	}
	new_val[i] = '\0';
	same_key_node->val = new_val;
	return ;
}

void	print_env(t_env *env_lst)
{
	t_env	*head;
	t_env	*tmp;

	head = env_lst;
	tmp = head;
	while (head != NULL)
	{
		printf("declare -x %s", head->key);
		if (head->val != NULL)
			printf("=\"%s\"", head->val);
		printf("\n");
		head = head->next;
	}
	env_lst = tmp;
}

int	builtin_export(t_cmds *cmds_info)
{
	char	*key;
	char	*val;
	char	*val_start;
	t_env	*same_key_node;
	size_t	i;

	if (cmds_info->cmd_args[1] == NULL)
		print_env(cmds_info->env_lst);
	else
	{
		i = 1;
		while ((cmds_info->cmd_args)[i] != NULL)
		{
			key = get_key(cmds_info->cmd_args[i], &val_start);
			if (is_wrong_key_name(key) == 1)
				return (1);
			val = get_val(val_start);
			same_key_node = search_same_key(cmds_info->env_lst, key);
			if (same_key_node == NULL)
				ft_lstadd_back_env(&(cmds_info->env_lst),
					ft_lstnew_env(key, val));
			else
				change_val(same_key_node, val);
			i++;
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:18:14 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/09 10:41:58 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_same_key(t_env *head, char *key)
{
	t_env	*tmp;

	tmp = head;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	head = tmp;
	return (NULL);
}

void	change_val(t_env *same_key_node, char *new_val)
{
	size_t	i;

	free(same_key_node->val);
	same_key_node->val = malloc(sizeof(char) * ft_strlen(new_val) + 1);	
	i = 0;
	while (new_val[i] != '\0')
	{
		(same_key_node->val)[i] = new_val[i];
		i++;
	}
	(same_key_node->val)[i] = '\0';
}

void	print_env(t_cmds *cmds_info)
{
	t_env	*head;
	t_env	*tmp;

	head = cmds_info->env_lst;
	tmp = head;
	while (head != NULL)
	{
		printf("declare -x %s=\"", head->key);
		if (head->val != NULL)
			printf("%s", head->val);
		printf("\"\n");
		head = head->next;
	}
	cmds_info->env_lst = tmp;
}

int	builtin_export(t_cmds *cmds_info)
{
	char	*key;
	char	*val;
	char	*val_start;
	t_env	*same_key_node;
	size_t	i;

	if (cmds_info->cmd_args[1] == NULL)
		print_env(cmds_info);
	else
	{
		i = 0;
		while (cmds_info->cmd_args[i] != NULL)
		{
			key = get_key(cmds_info->cmd_args[i], &val_start);
			val = get_val(val_start);
			same_key_node= search_same_key(cmds_info->env_lst, key);
			if (same_key_node == NULL)
				ft_lstadd_back_env(&(cmds_info->env_lst),
					ft_lstnew_env(key, val, 1));
			else
				change_val(same_key_node, val);
			i++;
		}
	}
	return (0);
}

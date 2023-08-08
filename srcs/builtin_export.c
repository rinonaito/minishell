/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:18:14 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/08 17:58:29 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_cmds *cmds_info)
{
	size_t	i;
	int	is_env;
	char	*key;
	char	*val;
	char	*val_start;

	i = 1;
	while (cmds_info->cmd_args[i] != NULL)
	{
		key = get_key(cmds_info->cmd_args[i], &val_start);	
		if (ft_strchr(cmds_info->cmd_args[i], '=') != NULL)
		{
			is_env = 1;
			val = get_val(val_start);
		}
		else
		{
			is_env = 0;
			val = NULL;
		}
		ft_lstadd_back_env(&(cmds_info->env_lst), ft_lstnew_env(key, val, is_env));
		i++;
	}
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

	if (cmds_info->cmd_args[1] != NULL)
		set_env(cmds_info);
	else
		print_env(cmds_info);
	return (0);
}

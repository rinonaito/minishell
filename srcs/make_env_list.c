/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:40:58 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/11 15:30:11 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char	*key, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->val = val;
	new->next = NULL;
	return (new);
}

t_env	*ft_lstlast_env(t_env *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void	ft_lstadd_back_env(t_env **head, t_env *new)
{
	t_env	*tail;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tail = ft_lstlast_env(*head);
	tail->next = new;
}

t_env	*make_env_lst(char	**env)
{
	t_env	*head;
	char	*key;
	char	*val;
	char	*val_start;
	size_t	i;

	head = NULL;
	val_start = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		key = get_key(env[i], &val_start);
		val = get_val(val_start);
		ft_lstadd_back_env(&head, ft_lstnew_env(key, val));
		i++;
	}
	return (head);
}

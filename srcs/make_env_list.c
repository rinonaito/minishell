/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:40:58 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/08 17:51:45 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char	*key, char *val, int is_env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->val = val;
	new->is_env = is_env;
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

char	*get_key(char *env, char **val_start)
{
	char	*start;
	char	*end;
	char	*key;

	start = env;
	end = ft_strchr(start, '=');
	if (end == NULL)
	{
		end = ft_strchr(start, '\0');
		*val_start = end;
	}
	else
		*val_start = end + 1;
	key = ft_strndup(start, end - start);
	return (key);
}

char	*get_val(char *val_start)
{
	char	*val;
	size_t	val_len;

	val_len = ft_strlen(val_start);
	val = ft_strndup(val_start, val_len);
	return (val);
}

t_env	*make_env_lst(char	**env)
{
	t_env	*head;
	char	*key;
	char	*val;
	char	*val_start;
	size_t	i;

	head = NULL;
	i = 0;
	val_start = NULL;
	while (env[i] != NULL)
	{
		key = get_key(env[i], &val_start);
		val = get_val(val_start);
		ft_lstadd_back_env(&head, ft_lstnew_env(key, val, 1));
		i++;
	}
	return (head);
}

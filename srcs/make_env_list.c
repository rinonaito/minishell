/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:40:58 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/20 16:12:07 by rnaito           ###   ########.fr       */
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

char	*get_key(char **env)
{
	char	*start;
	char	*end;
	char	*key;

	start = *env;
	end = ft_strchr(start, '=');
	key = ft_strndup(start, end - start);
	*env = end + 1;
	return (key);
}

char	*get_val(char *env)
{
	char	*val;
	size_t	val_len;

	val_len = ft_strlen(env);
	val = ft_strndup(env, val_len);
	return (val);
}

t_env	*make_env_list(char	**env)
{
	t_env	*head;
	t_env	*new;
	char	*key;
	char	*val;
	size_t	i;

	head = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		key = get_key(&env[i]);
		val = get_val(env[i]);
		new = ft_lstnew_env(key, val);
		ft_lstadd_back_env(&head, new);
		i++;
	}
	return (head);
}

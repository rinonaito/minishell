/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:06:44 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/11 15:13:20 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wrong_key_name(char *key)
{
	size_t	i;

	if (key == NULL)
		return (1);
	if (ft_isalpha(key[0]) != 1 && key[0] != '_')
		return (1);
	i = 1;
	while (key[i] != '\0')
	{
		if (ft_isalnum(key[i]) != 1 && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

t_env	*search_same_key(t_env *head, char *key)
{
	t_env	*tmp;

	tmp = head;
	while (head != NULL)
	{
		if (ft_strequ(head->key, key))
			return (head);
		head = head->next;
	}
	head = tmp;
	return (NULL);
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
		*val_start = NULL;
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

	if (val_start == NULL)
		return (NULL);
	val_len = ft_strlen(val_start);
	if (val_len == 0)
	{
		val = malloc(sizeof(char));
		*val = '\0';
	}
	else
		val = ft_strndup(val_start, val_len);
	return (val);
}

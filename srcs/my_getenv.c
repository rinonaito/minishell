/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:14:22 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/08 11:40:29 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(char *key, t_env *env_lst)
{
	char	*val;
	t_env	*tmp;

	tmp = env_lst;
	val = NULL;
	while (env_lst != NULL && val == NULL)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			val = env_lst->val;
		env_lst = env_lst->next;
	}
	return (val);
}

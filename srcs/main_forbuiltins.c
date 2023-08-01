/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:53:30 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/25 21:25:37 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
//	size_t	i;
	t_env	*head;

	head = make_env_list(env);
	builtin_env(head);
//	head = make_env_list(env);
//	while (head != NULL)
//	{
//		printf("key = %s, val = %s\n", head->key, head->val);
//		head = head->next;
//	}
//	while (env[i] != NULL)
//	{
//		printf("env[%zu] = %s\n", i, env[i]);
//		i++;
//	}
	return (0);
}

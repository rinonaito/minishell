/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:41:43 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/24 17:56:29 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_list(t_token **param, int status, t_env *env_lst)
{
	char		*to_be_expanded;
	char		*expanded;
//	char		*splitted;
//	char		*new_token;
	char		*temp_token;
	t_token		*temp;

	temp = *param;
	while (*param != NULL)
	{
		to_be_expanded = (*param)->token;
		if (to_be_expanded != NULL)
			expanded = ft_expand_str(to_be_expanded, status, env_lst, false);
		printf("env_expanded = %s\n", expanded);
//		splitted = split_expanded_word(expanded, env_lst);
//		printf("splitted = %s\n", splitted);
//		new_token = remove_quotes(expanded);
//		if (new_token != NULL)
//		{
//			temp_token = (*param)->token;
//			(*param)->token = new_token;
//			free(temp_token);
//		}
		temp_token = (*param)->token;
		(*param)->token = expanded;
		free(temp_token);
		*param = (*param)->next;
	}
	*param = temp;
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:41:43 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/23 17:33:33 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_list(t_token **param, int status, t_env *env_lst)
{
	char		*old_token;
	char		*env_expanded;
	char		*new_token;
	char		*temp_token;
	t_token		*temp;

	temp = *param;
	while (*param != NULL)
	{
		old_token = (*param)->token;
		if (old_token != NULL)
			env_expanded = ft_expand_str(old_token, status, env_lst);
		printf("env_expanded = %s\n", env_expanded);
		split_expanded_word(*param, env_lst);
		new_token = remove_quotes(env_expanded);
		if (new_token != NULL)
		{
			temp_token = (*param)->token;
			(*param)->token = new_token;
			free(temp_token);
		}
		*param = (*param)->next;
	}
	*param = temp;
	return ;
}

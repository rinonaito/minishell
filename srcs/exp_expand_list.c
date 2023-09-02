/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:41:43 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/02 16:28:37 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *for_syntax_error(char *to_be_expanded, int *ret)
{
	char	*expanded;

	expanded = ft_strndup(to_be_expanded, ft_strlen(to_be_expanded));
	if (to_be_expanded == NULL)
		ft_perror("malloc");
	free(to_be_expanded);
	*ret = 1;
	return (expanded);
}

int	expand_list(t_token **head, int exit_status, t_env *env_lst)
{
	char		*to_be_expanded;
	char		*expanded;
	t_token		*temp;
	int			ret;

	temp = *head;
	ret = 0;
	while (*head != NULL)
	{
		to_be_expanded = (*head)->token;
		if (to_be_expanded != NULL)
		{
			expanded = expand_str(to_be_expanded, exit_status,
					env_lst, FOR_NORMAL);
			if (expanded == NULL)
			{
				expanded = for_syntax_error(to_be_expanded, &ret);
//				expanded = ft_strndup(to_be_expanded,
//						ft_strlen(to_be_expanded));
//				free(to_be_expanded);
//				ret = 1;
			}
			(*head)->token = expanded;
		}
		*head = (*head)->next;
	}
	*head = temp;
	return (ret);
}

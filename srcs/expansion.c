/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:21:01 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/19 15:52:33 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_quotes(char *old_start)
{
	char	*new_start;

	if (*old_start == '\'')
	{
		new_start = ft_skip_to_closing_quote(old_start);
		if (new_start != NULL)
			return (new_start);
	}
	return (old_start);
}

char	*ft_expand_str(char *old_token)
{
	char		*new_start;
	char		*new_token;
	int			reset_i;
	int			i;

	new_token = NULL;
	reset_i = 0;
	i = 0;
	while (old_token[i] != '\0')
	{
		new_start = ft_check_quotes(&old_token[i]);
		i += new_start - &old_token[i];
		if (old_token[i] == '$')
		{
			new_token = ft_replace_key_with_val(&old_token, &old_token[i]);
			if (new_token != NULL)
				i = -1;
		}
		i++;
	}
	return (new_token);
}

void	ft_expand_list(t_token **param)
{
	char		*old_token;
	char		*new_token;
	char		*temp_token;
	t_token		*temp;

	temp = *param;
	while (*param != NULL)
	{
		old_token = (*param)->token;
		if (old_token != NULL)
			new_token = ft_expand_str(old_token);
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

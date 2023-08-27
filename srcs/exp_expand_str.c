/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:37:50 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/26 18:47:31 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_of_quoted_str(char *to_be_checked, int *expand_mode)
{
	char	*closing_quote;
	int	len_of_quoted_str;

	len_of_quoted_str = 0;
	if (*expand_mode != FOR_HEREDOC && *to_be_checked == '\'')
	{
		closing_quote = skip_to_closing_quote(to_be_checked);
		len_of_quoted_str = closing_quote - to_be_checked;
	}
	return (len_of_quoted_str);
}

char	*ft_expand_str(char *to_be_expanded, int exit_status, t_env *env_lst,
				int expand_mode)
{
	char		*env_key;
	char		*env_val;
	char		*env_expanded;
	int			i;
	int		is_error;

	env_expanded = NULL;
	i = 0;
	while (to_be_expanded != NULL && to_be_expanded[i] != '\0')
	{
		i += get_len_of_quoted_str(&to_be_expanded[i], &expand_mode);
		if (to_be_expanded[i] == '$')
		{
			env_key = get_key_of_env(&to_be_expanded[i], &is_error);
			if (is_error)
				printf("bad_sbsti!!!\n");
			env_val = get_val_of_env(env_key, exit_status, env_lst, expand_mode);
			env_expanded = replace_key_with_val(to_be_expanded,
				&to_be_expanded[i], env_key, env_val);
			to_be_expanded = env_expanded;
			i = -1;
		}
			
		i++;
	}
	if (env_expanded == NULL)
	{
		if (to_be_expanded != NULL)
			env_expanded = ft_strndup(to_be_expanded, ft_strlen(to_be_expanded));
		else
			env_expanded = NULL;
	}
	if (expand_mode == FOR_HEREDOC)
		return (env_expanded);
	else
		return (remove_quotes(env_expanded));
}


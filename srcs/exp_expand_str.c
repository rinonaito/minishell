/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:37:50 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/31 00:54:49 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_of_quoted_str(char *to_be_checked, int *expand_mode)
{
	char	*closing_quote;
	int		len_of_quoted_str;

	len_of_quoted_str = 0;
	if (*expand_mode != FOR_HEREDOC && *to_be_checked == '\'')
	{
		closing_quote = skip_to_closing_quote(to_be_checked);
		len_of_quoted_str = closing_quote - to_be_checked;
	}
	return (len_of_quoted_str);
}

static int	check_expand_mode(int expand_mode, char *to_be_expanded, int i)
{
	int	j;
	int	num_of_d_quotes;

	num_of_d_quotes = 0;
	if (expand_mode == FOR_HEREDOC)
		return (FOR_HEREDOC);
	else
	{
		j = 0;
		while (j <= i)
		{
			if (to_be_expanded[j] == '\"')
				num_of_d_quotes++;
			j++;
		}
		if (num_of_d_quotes == 0 || num_of_d_quotes % 2 == 0)
			return (FOR_NORMAL);
		else
			return (FOR_D_QUOTED);
	}
}

static char	*for_token_without_env(char *env_expanded, char *to_be_expanded)
{
	if (env_expanded == NULL)
	{
		if (to_be_expanded != NULL)
		{
			env_expanded = ft_strndup(to_be_expanded,
					ft_strlen(to_be_expanded));
			free (to_be_expanded);
		}
		else
			env_expanded = NULL;
	}
	return (env_expanded);
}

static void	get_ready_for_next_env(char **to_be_expanded, char *expanded,
		int *i)
{
	*to_be_expanded = expanded;
	*i = -1;
}

char	*expand_str(char *to_be_expanded, int exit_status, t_env *env_lst,
				int expand_mode)
{
	char		*env_key;
	char		*env_val;
	char		*expanded;
	int			i;

	expanded = NULL;
	i = 0;
	while (to_be_expanded != NULL && to_be_expanded[i] != '\0')
	{
		i += get_len_of_quoted_str(&to_be_expanded[i], &expand_mode);
		if (to_be_expanded[i] == '$')
		{
			expand_mode = check_expand_mode(expand_mode, to_be_expanded, i);
			env_key = get_key(&to_be_expanded[i]);
			env_val = get_val(env_key, exit_status, env_lst, expand_mode);
			expanded = replace_key_with_val(to_be_expanded,
					&to_be_expanded[i], env_key, env_val);
			get_ready_for_next_env(&to_be_expanded, expanded, &i);
		}
		i++;
	}
	expanded = for_token_without_env(expanded, to_be_expanded);
	return (remove_quotes_if_needed(expanded, expand_mode));
}

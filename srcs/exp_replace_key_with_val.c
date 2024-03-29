/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_replace_key_with_val.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:18:01 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/02 16:37:32 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_new_token(char *original_token, char *doller,
					char *key, char *val)
{
	char	*new_token;
	int		len_key;
	int		len_val;
	int		len_token;

	len_key = ft_strlen(key);
	if (val == NULL)
		val = "\0";
	len_val = ft_strlen(val);
	len_token = ft_strlen(original_token);
	if (*(doller + 1) == '{')
		len_key += 2;
	new_token = malloc(len_token - len_key + len_val + 1);
	if (new_token == NULL)
		ft_perror("malloc");
	if (new_token != NULL)
	{
		ft_strlcpy(new_token, original_token, doller - original_token + 1);
		ft_strlcat(new_token, val, len_token + len_val);
		ft_strlcat(new_token, doller + len_key + 1,
			len_token - len_key + len_val);
	}
	return (new_token);
}

char	*replace_key_with_val(char *old_token, char *doller,
					char *env_key, char *env_val)
{
	char		*new_token;

	if (env_key == NULL)
		return (NULL);
	new_token = make_new_token(old_token, doller, env_key, env_val);
	free (env_val);
	env_val = NULL;
	free (env_key);
	env_key = NULL;
	free (old_token);
	old_token = NULL;
	return (new_token);
}

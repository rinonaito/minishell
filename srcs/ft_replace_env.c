/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:11:52 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/14 21:29:25 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_for_braced_env(char **start, char **end, char *doller)
{
	int	is_error;
	
	is_error = 0;
	*start = doller + 2;
	*end = ft_strchr(*start, '}');
	if (*end == NULL)
		is_error = 1;
	return (is_error);
}

void	ft_for_unbraced_env(char **start, char **end, char *doller)
{
	size_t	i;

	*start = doller + 1;
	i = 0;
	while ((*start)[i] != '\0')
	{
		if (ft_isalnum((*start)[i]) == 0 && (*start)[i] != '_')
		{
			*end = &((*start)[i]);
			break ;
		}
		i++;
	}
	if (*end == NULL)
		*end = &((*start)[i]);
}

char	*ft_get_key_of_env(char *doller)
{
	char	*start;
	char	*end;
	char	*env_key;
	int		is_error;

	start = NULL;
	end = NULL;
	if (*(doller + 1) == '{')
	{
		is_error = ft_for_braced_env(&start, &end, doller);
		if (is_error == 1)
			return (NULL);
	}
	else
		ft_for_unbraced_env(&start, &end, doller);
	if (start != NULL && end != NULL)
		env_key = ft_strndup(start, end - start);
	else
		return (NULL);
	return (env_key);
}

char	*ft_make_new_token(char *token, char *doller, char *before, char *after)
{
	char	*new_token;
	int		len_before;
	int		len_after;
	int		len_token;

	len_before = ft_strlen(before);
	len_after = ft_strlen(after);
	len_token = ft_strlen(token);
	if (*(doller + 1) == '{')
		len_before += 2;
	new_token = malloc(len_token - len_before + len_after + 1);
	ft_strlcpy(new_token, token, doller - token + 1);
	ft_strlcat(new_token, after, len_token + len_after);
	ft_strlcat(new_token, doller + len_before + 1,
		len_token - len_before + len_after);
	return (new_token);
}

int	ft_replace_env(t_tree *root, char **old_token, char *doller)
{
	char		*env_key;
	char		*env_val;
	char		*new_token;
	char		*temp;

	env_key = ft_get_key_of_env(doller);
	if (env_key != NULL)
	{
		env_val = getenv(env_key);
		if (env_val == NULL)
			env_val = "\0";
		new_token = ft_make_new_token(*old_token, doller, env_key, env_val);
		*old_token = new_token;
		temp = root->param->token;
		root->param->token = new_token;
		free (temp);
		free (env_key);
		return (1);
	}
	else
		return (0);
}

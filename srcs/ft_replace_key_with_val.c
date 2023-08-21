/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_key_with_val.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:11:52 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/21 20:33:39 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_for_braced_env(char **start, char **end, char *doller)
{
	int		is_error;
	size_t	i;

	is_error = 0;
	*start = doller + 2;
	*end = ft_strchr(*start, '}');
	if (*end == NULL || ft_isdigit((int)**start) == 1)
		is_error = 1;
	i = 0;
	while (is_error == 0 && (*start)[i] != '}')
	{
		if (ft_isalnum((*start)[i]) == 0 && (*start)[i] != '_')
			is_error = 1;
		i++;
	}
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
	if (ft_isdigit((int)*start[0]) == 1)
		*end = &((*start)[0]);
	if (*start[0] == '?')
		*end = &((*start)[1]);
}

char	*ft_get_key_of_env(char *doller, int *is_error)
{
	char	*start;
	char	*end;
	char	*env_key;

	start = NULL;
	end = NULL;
	if (*(doller + 1) == '{')
		*is_error = ft_for_braced_env(&start, &end, doller);
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

char	*ft_replace_key_with_val(char **old_token, char *doller, int status, t_env *env_lst)
{
	char		*env_key;
	char		*env_val;
	char		*new_token;
	int			is_error;

	is_error = 0;
	env_val = NULL;
	env_key = ft_get_key_of_env(doller, &is_error);
	if (ft_strequ(env_key, "?"))
		env_val = ft_itoa(status);
	if (is_error == 1 && env_val == NULL)
		ft_perror("bad substitution");
	if (env_key != NULL)
	{
		if (env_val == NULL)
			env_val = my_getenv(env_key, env_lst);
		if (env_val == NULL)
			env_val = "\0";
		new_token = ft_make_new_token(*old_token, doller, env_key, env_val);
		*old_token = new_token;
		free (env_key);
		return (new_token);
	}
	else
		return (NULL);
}

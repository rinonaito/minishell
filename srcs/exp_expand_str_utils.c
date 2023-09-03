/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_str_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:37:50 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/02 21:33:57 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	for_braced_env(char **start, char **end, char *doller)
{
	int		is_error;
	size_t	i;

	is_error = 0;
	*start = doller + 2;
	*end = ft_strchr(*start, '}');
	if (*end == NULL || ft_isdigit((int)**start) == 1 || *start == *end)
		is_error = 1;
	i = 0;
	while (is_error == 0 && (*start)[i] != '}')
	{
		if (ft_isalnum((*start)[i]) == 0 && (*start)[i] != '_')
			is_error = 1;
		i++;
	}
	if (is_error)
	{
		*start = NULL;
		*end = NULL;
	}
	return ;
}

static void	for_unbraced_env(char **start, char **end, char *doller)
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

char	*get_key(char *doller)
{
	char	*start;
	char	*end;
	char	*env_key;

	start = NULL;
	end = NULL;
	if (*(doller + 1) == '{')
		for_braced_env(&start, &end, doller);
	else
		for_unbraced_env(&start, &end, doller);
	if (start != NULL && end != NULL && start != end)
	{
		env_key = ft_strndup(start, end - start);
		if (env_key == NULL)
			ft_perror("malloc");
	}
	else
		return (NULL);
	return (env_key);
}

char	*get_val(char *env_key, int exit_status, t_env *env_lst,
				int expand_mode)
{
	char	*env_val;

	if (env_key == NULL)
		return (NULL);
	if (ft_strequ(env_key, "?"))
		return (ft_itoa(exit_status));
	env_val = my_getenv(env_key, env_lst);
	if (env_val == NULL)
		return (NULL);
	if (expand_mode == FOR_NORMAL)
		env_val = split_expanded_word(env_val, env_lst);
	else
		env_val = ft_strndup(env_val, ft_strlen(env_val));
	if (env_val == NULL)
		ft_perror("malloc");
	return (env_val);
}

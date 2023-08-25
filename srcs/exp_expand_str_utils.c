/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_str_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:37:50 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/25 23:35:33 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	for_braced_env(char **start, char **end, char *doller)
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


char	*get_key_of_env(char *doller, int *is_error)
{
	char	*start;
	char	*end;
	char	*env_key;

	start = NULL;
	end = NULL;
	*is_error = 0;
	if (*(doller + 1) == '{')
		*is_error = for_braced_env(&start, &end, doller);
	else
		for_unbraced_env(&start, &end, doller);
	if (start != NULL && end != NULL)
		env_key = ft_strndup(start, end - start);
	else
		return (NULL);
	return (env_key);
}

char	*get_val_of_env(char *env_key, int exit_status, t_env *env_lst,
				bool is_heredoc)
{
	char	*env_val;
	char	*splitted;

	if (ft_strequ(env_key, "?"))
		env_val = ft_itoa(exit_status);
	else if (env_key != NULL)
	{
		env_val = my_getenv(env_key, env_lst);
		if (env_val == NULL)
			env_val = "\0";
	}
	if (!is_heredoc)
	{
		splitted = split_expanded_word(env_val, env_lst);
		return (splitted);
	}
	return (env_val);
}

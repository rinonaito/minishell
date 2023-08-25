/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_expand_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:37:50 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/25 14:18:07 by rnaito           ###   ########.fr       */
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

static int	get_len_of_quoted_str(char *to_be_checked, bool is_heredoc)
{
	char	*closing_quote;
	int	len_of_quoted_str;

	len_of_quoted_str = 0;
	if (!is_heredoc && *to_be_checked == '\'')
	{
		closing_quote = skip_to_closing_quote(to_be_checked);
		len_of_quoted_str = closing_quote - to_be_checked;
	}
	return (len_of_quoted_str);
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

char	*get_val_of_env(char *env_key, int exit_status, t_env *env_lst, bool is_heredoc)
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

char	*ft_expand_str(char *to_be_expanded, int exit_status, t_env *env_lst, bool is_heredoc)
{
	char		*env_expanded;
	int			i;
	char	*env_key;
	char	*env_val;
	int		is_error;

	if (to_be_expanded == NULL)
		return (NULL);
	env_expanded = NULL;
	i = 0;
	while (to_be_expanded[i] != '\0')
	{
		i += get_len_of_quoted_str(&to_be_expanded[i], is_heredoc);
		if (to_be_expanded[i] == '$')
		{
			env_key = get_key_of_env(&to_be_expanded[i], &is_error);
			if (is_error)
				printf("bad_sbsti!!!\n");
			env_val = get_val_of_env(env_key, exit_status, env_lst, is_heredoc);
			env_expanded = replace_key_with_val(to_be_expanded, &to_be_expanded[i], env_key, env_val);
			to_be_expanded = env_expanded;
			i = -1;
		}
		i++;
	}
	if (env_expanded == NULL)
		env_expanded = ft_strndup(to_be_expanded, ft_strlen(to_be_expanded));
	if (is_heredoc)
		return (env_expanded);
	else
		return (remove_quotes(env_expanded));
}


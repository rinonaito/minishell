/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:11:52 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/06 17:26:22 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(char *str)
{
	size_t	i;
	char	*start;
	char	*end;
	char	*env;

	i = 1;
	if (str[i] == '{')
	{
		start = &str[i + 1];
		end = ft_strchr(start, '}');
	}
	else
	{
		start = &str[i];
		end = ft_strchrchr(start, ' ', '\t', 0);
		if (end == NULL)
			end = ft_strchr(start, '\0');
	}
	env = ft_strndup(start, end - start);
	return (env);
}

char	*ft_find_env(char *token)
{
	size_t	i;
	char	*env;

	env = NULL;
	i = 0;
	while (token[i] != '\0')	
	{
		if (token[i] == '$')
		{
			env = ft_get_env(&token[i]);
			return (env);
		}
		i++;
	}
	return (NULL);
}

void	ft_expand_env(t_tree *root)
{

}

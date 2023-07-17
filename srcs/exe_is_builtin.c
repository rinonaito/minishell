/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_is_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 23:34:09 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/17 13:23:59 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//@func: check if a string is equal to one of the builtin commands
int	is_builtin(char *s)
{
	const char	*lst[] = {"echo", "cd", "pwd", "export", "unset", \
												"env", "exit", NULL};
	int			i;

	if (!s)
		return (0);
	i = 0;
	while (lst[i])
	{
		if (ft_strnequ(lst[i], s))
			return (1);
		i++;
	}
	return (0);
}

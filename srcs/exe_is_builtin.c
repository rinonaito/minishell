/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_is_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 23:34:09 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/11 23:51:30 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//@func: check if a string is equal to one of the builtin commands
int	is_builtin(char *s)
{
	const char	*lst[] = {"echo", "cd", "pwd", "export", "unset", \
												"env", "exit", NULL};

	if (!s)
		return (0);
	while (lst)
	{
		if (ft_strnequ(lst, s))
			return (1);
		lst++;
	}
	return (0);
}

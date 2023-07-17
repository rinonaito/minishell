/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_call_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:16:53 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/17 13:29:04 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	call_builtin(char *cmd)
{
	const char	*lst[] = {"echo", "cd", "pwd", "export", "unset", \
												"env", "exit", NULL};
	int			i;


	printf(">%s\n", __func__);
	if (!cmd)
		return ;
	i = 0;
	while (lst[i])
	{
		if (ft_strnequ(lst[i], cmd))
		{
			printf(" calling builin\n");
			return ;
		}
		i++;
	}
	return ;
}

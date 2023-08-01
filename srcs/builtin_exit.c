/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:37:47 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/01 00:11:19 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int		within_long(char *s)
{
	long long	x;
	long		sign;

	if (!s)
		return (0);
	sign = 1;
	if (*s == '-')
		sign = -1;
	if (*s == '+' || *s == '-')
		s++;
	x = 0;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (1);
		if (sign == -1)
		{
			if (x > LONG_MAX / 10 || (x == LONG_MAX / 10 && *s >= '8')
				return (1);
		}
		else if (x > LONG_MAX / 10 || (x == LONG_MAX / 10 && *s >= '7')
				return (1);
		x = x * 10 + (*s - '0');
		s++;
	}
	return (0);
}

int		builtin_exit(t_cmds *cmds_info)
{
	char	**cmd_args;

	cmd_args = cmds_info->cmd_args;
	if (!cmd_args)
		return (-1);
	if (!cmd_args[2])
	{
		ft_printf_fd(2, "bash: exit: too many arguments\n");
	}
	return (0);
}

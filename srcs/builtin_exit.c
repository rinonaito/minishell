/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 23:37:47 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/03 21:20:53 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static long	ft_atol(char *s)
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
	while (*s && ft_isdigit(*s))
	{
		if (sign == -1)
		{
			if (x > LONG_MAX / 10 || (x == LONG_MAX / 10 && *s >= '8'))
				return (LONG_MIN);
		}
		else if (x > LONG_MAX / 10 || (x == LONG_MAX / 10 && *s >= '7'))
			return (LONG_MAX);
		x = x * 10 + (*s - '0');
		s++;
	}
	return (sign * x);
}

static int	within_long(char *s)
{
	long long	x;
	long		sign;

	sign = 1;
	if (*s == '-')
		sign = -1;
	if (*s == '+' || *s == '-')
		s++;
	x = 0;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		if (sign == -1)
		{
			if (x > LONG_MAX / 10 || (x == LONG_MAX / 10 && *s > '8'))
				return (0);
		}
		else if (x > LONG_MAX / 10 || (x == LONG_MAX / 10 && *s > '7'))
			return (0);
		x = x * 10 + (*s - '0');
		s++;
	}
	return (1);
}

static int	convert_exit_format(char *str)
{
	long	val;

	val = ft_atol(str);
	if (val >= 0)
		return (val % 256L);
	else
		return (256L + val % 256L);
}

void	builtin_exit(t_cmds *cmds_info)
{
	char	**cmd_args;

	cmd_args = cmds_info->cmd_args;
	if (!cmd_args || !cmd_args[1])
		exit(0);
	else if (cmd_args[2])
	{
		if (!within_long(cmd_args[1]))
		{
			ft_printf_fd(2, "minishell: exit: numeric arguments required\n");
			exit(255);
		}
		else
		{
			ft_printf_fd(2, "minishell: exit: too many arguments\n");
			return ;
		}
	}
	else if (!within_long(cmd_args[1]))
	{
		ft_printf_fd(2, "minishell: exit: numeric arguments required\n");
		exit(255);
	}
	exit(convert_exit_format(cmd_args[1]));
}

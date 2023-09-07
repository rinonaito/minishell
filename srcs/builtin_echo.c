/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:24 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/07 15:47:35 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	valid_echo_option(char *str)
{
	size_t	i;
	bool	includes_n;

	if (str[0] != '-')
		return (0);
	i = 1;
	includes_n = false;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		includes_n = true;
		i++;
	}
	if (includes_n)
		return (1);
	return (0);
}

int	builtin_echo(t_cmds *cmds_info)
{
	char	**cmd_args;
	bool	new_line;
	int		i;

	cmd_args = cmds_info->cmd_args;
	new_line = true;
	if (!cmd_args || !cmd_args[0])
		return (1);
	i = 1;
	//while (cmd_args[i] && ft_strequ(cmd_args[i], "-n"))
	while (cmd_args[i] && valid_echo_option(cmd_args[i]))
	{
		i++;
		new_line = false;
	}
	while (cmd_args[i])
	{
		ft_printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}

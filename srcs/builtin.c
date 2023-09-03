/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:16:53 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/03 20:48:03 by taaraki          ###   ########.fr       */
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
		if (ft_strequ(lst[i], s))
			return (1);
		i++;
	}
	return (0);
}

int	call_builtin(t_cmds *cmds_info)
{
	int	ret;

	if (!cmds_info)
		return (-1);
	ret = 0;
	if (ft_strequ(cmds_info->cmd_args[0], "echo"))
		ret = builtin_echo(cmds_info);
	else if (ft_strequ(cmds_info->cmd_args[0], "cd"))
		ret = builtin_cd(cmds_info);
	else if (ft_strequ(cmds_info->cmd_args[0], "pwd"))
		ret = builtin_pwd();
	else if (ft_strequ(cmds_info->cmd_args[0], "env"))
		ret = builtin_env(cmds_info);
	else if (ft_strequ(cmds_info->cmd_args[0], "export"))
		ret = builtin_export(cmds_info);
	else if (ft_strequ(cmds_info->cmd_args[0], "unset"))
		ret = builtin_unset(cmds_info);
	else if (ft_strequ(cmds_info->cmd_args[0], "exit"))
	{
		builtin_exit(cmds_info);
		ret = 1;
	}
	return (ret);
}

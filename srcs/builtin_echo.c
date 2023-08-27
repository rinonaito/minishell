/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:36:24 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/27 20:47:10 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int    builtin_echo(t_cmds *cmds_info)
{
	char	**cmd_args;
    bool    new_line;
    int   	i;

	cmd_args = cmds_info->cmd_args;
    new_line = true;
	if (!cmd_args || !cmd_args[0])
		return (1);
	i = 1;
    while (cmd_args[i])
    {
		if (i == 1 && ft_strequ(cmd_args[1], "-n"))
		{
        	new_line = false;
			i++;
			continue ;
		}
        printf("%s", cmd_args[i]);
        if (cmd_args[i + 1])
			printf(" ");
		i++;
    }
    if (new_line)
        printf("\n");
    return (0);
}

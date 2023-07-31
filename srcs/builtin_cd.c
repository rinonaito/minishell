/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:55:33 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/31 20:41:17 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//#include	<unistd.h>

/*
typedef struct s_cmds{
	char	**cmd_args;
	char	**env;
	pid_t	*pid_ary;
	int		num_cmds;
	int		i;
}					t_cmds;
*/

int		absolute_path(char *path)
{
	int		ret;

	printf(" >%s\n", __func__);
	ret = chdir(path);
	return (ret);
}

// cd /path
// 0  1
int		builtin_cd(t_cmds *cmds_info)
{
	char	**cmd_args;
	char	buff_cwd[PATH_MAX];
	int		ret;

	//option 1. absolute path
	//option 2. relative path

	printf(" >%s\n", __func__);
	ft_memset(buff_cwd, '\0', PATH_MAX);
	getcwd(buff_cwd, PATH_MAX);
	printf("buff_cwd:[%s]\n", buff_cwd);
	cmd_args = cmds_info->cmd_args;
	if (!cmd_args)
		return (-1);//error
	if (!cmd_args[1])
	{
		//go to the home directory
		char home[] = "/Users/taaraki";
		ret = chdir(home);
	}
	else
	{
		//if (ft_strequ("/", &cmd_args[1][0]))
		if (ft_strncmp("/", cmd_args[1], 1) == 0)
			ret = absolute_path(cmd_args[1]);
		//else
			//ret = relative_path(cmd_args[1]);
	}
	return (ret);
}

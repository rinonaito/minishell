/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:16:53 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/03 20:43:06 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//@func: check if a string is equal to one of the builtin commands
int	is_builtin(char *s)
{
	const char	*lst[] = {"echo", "cd", "pwd", "export", "unset", \
												"env", "exit", NULL};
	//const char	*lst[] = {"echo", "cd", "export", "unset", \
												//"env", "exit", NULL};
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

//void	call_builtin(int fd[2], char **cmd_args, int j, int num_cmds)
void	call_builtin(int pipe_fd[2], t_cmds *cmds_info)
{
	const char	*lst[] = {"echo", "cd", "pwd", "export", "unset", \
												"env", "exit", NULL};
	int			i;

//	printf(">%s\n", __func__);
//	if (!cmds_info->cmd_args || !cmds_info->cmd_args[0])
//		return ;
	i = 0;
	while (lst[i])
	{
		if (ft_strequ(lst[i], cmds_info->cmd_args[0]))
		{
//			printf(" calling builin function : %s\n",lst[i]); 
			built_in_process(pipe_fd, cmds_info);
			return ;
		}
		i++;
	}
	return ;
}

void	built_in_process(int pipe_fd[2], t_cmds *cmds_info)
{
//	printf(">%s\n", __func__);
	if (builtin_echo(cmds_info) == 0)
		exit(0);
	else
		exit(1);
}


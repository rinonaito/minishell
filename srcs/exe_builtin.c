/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:16:53 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/23 18:10:46 by rnaito           ###   ########.fr       */
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
	printf("in BUILTIN PROCESS\nfd[0] = %d, fd[1] = %d\n", pipe_fd[0], pipe_fd[1]);
	printf("close READ_END(%d)\n", pipe_fd[READ_END]);
	if (pipe_fd[READ_END] != STDIN_FILENO)
		close(pipe_fd[READ_END]);
	printf("cmds_info->i = %d, cmds_info->num_cmds = %d\n",cmds_info->i , cmds_info->num_cmds);
//	if (cmds_info->i < cmds_info->num_cmds)//i is the index of command starting from 1
	{
		//printf(" (i < numcmds)\n");
		if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		{
			close(pipe_fd[WRITE_END]);
			ft_perror("dup2");
		}
	}
	//else
		//printf(" !(i < numcmds)\n");
	//printf(" outside (should not be seen on the display unless !(i < numcmds))\n");
	printf("close WRITE_END(%d)\n", pipe_fd[WRITE_END]);
	if (pipe_fd[WRITE_END] != STDOUT_FILENO)
		close(pipe_fd[WRITE_END]);//why close
	//execute_builtin(cmd_args);
	{
//		printf(" ***** %s *****\n", cmds_info->cmd_args[0]);
		if (builtin_echo(cmds_info->cmd_args) == 0)
			exit(0);
		else
			exit(1);
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:16:53 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/31 22:28:16 by taaraki          ###   ########.fr       */
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
//	if (pipe_fd[READ_END] != STDIN_FILENO)
//		close(pipe_fd[READ_END]);
	//printf("IN BUILTIN\npipe_fd[READ_END] = [%d]\npipe_fd[WRITE_END] = [%d]\n", pipe_fd[READ_END], pipe_fd[WRITE_END]);
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
	{
		close(pipe_fd[READ_END]);
		ft_perror("dup2");
	}
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
	{
		close(pipe_fd[WRITE_END]);
		ft_perror("dup2");
	}
//	if (pipe_fd[WRITE_END] != STDOUT_FILENO)
//		close(pipe_fd[WRITE_END]);//why close
	//execute_builtin(cmd_args);
	{
		//if (builtin_echo(cmds_info->cmd_args) == 0)
			//exit(0);
		//else
			//exit(1);
		int ret = builtin_cd(cmds_info);
		printf(" ret:[%d]\n", ret);
		if (ret == -1)
			exit(1);
		else
			exit(0);
	}
}


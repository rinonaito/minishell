/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/26 16:50:11 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<errno.h>

void	parent_process(int pipe_fd[2], t_cmds *cmds_info)
{
	/*** pipein ***/

//	printf(">%s\n", __func__);
	int		status;

//	if (pipe_fd[WRITE_END] != STDOUT_FILENO)
//		close(pipe_fd[WRITE_END]);
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
	{
//		close(pipe_fd[READ_END]);
		ft_perror("dup2");
	}
//	printf("DUP: STDIN will be tread");
//	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
//	{
//		close(pipe_fd[WRITE_END]);
//		ft_perror("dup2");
//	}
	//close it to free the resource
	if (pipe_fd[READ_END] != STDIN_FILENO)
		close(pipe_fd[READ_END]);
}

static void	exec(char **cmd_args, char **env)
{
	char	*file;

	int	i = 0;
	printf(">%s\n", __func__);
	//int i = -1;
	//hile (env[++i])
		//printf("env[%d]:[%s]\n", i, env[i]);
	if (!cmd_args)
		return ;
	file = ft_search_path(cmd_args[0]);//get the path to the command
	//if (access(file, F_OK | X_OK) == 0)
	//{
		//printf(" access success");
		//if (execve(file, cmd_args, env) == -1)
			//ft_perror(" command not found");
	//}
	//else
	//{
		//ft_perror(" access failed");
	//}
//	for (int i = 0; cmd_args[i] != NULL; i++)
//	{
//		printf("cmd_args[%d] = [%s]\n", i, cmd_args[i]);
//	}
//	dprintf(2, " env:[%p]\n", env);
//	dprintf(2, " ERRORNO:[%s], [%d]\n", strerror(errno), errno);

	int ret = execve(file, cmd_args, env);
//	printf(" ret:[%d]\n", ret);
	//if (execve(file, cmd_args, env) == -1)
		//ft_perror(" command not found");
}

//void	child_process(int pipe_fd[2], int file_fd[2], t_cmds *cmds_info)
void	child_process(int pipe_fd[2], t_cmds *cmds_info)
{
	/*** 1.fdin ***/
	/*** 2.pipeout ***/
	/*** 3.fdout ***/

//	if (pipe_fd[READ_END] != STDIN_FILENO)
//	close(pipe_fd[READ_END]);
	printf("IN CHILD\npipe_fd[READ_END] = [%d]\npipe_fd[WRITE_END] = [%d]\n", pipe_fd[READ_END], pipe_fd[WRITE_END]);
//	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
//	{
//		close(pipe_fd[READ_END]);
//		ft_perror("dup2");
//	}
//	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
//	{
//		close(pipe_fd[WRITE_END]);
//		ft_perror("dup2");
//	}
//	if (pipe_fd[WRITE_END] != STDOUT_FILENO)
//		close(pipe_fd[WRITE_END]);//close it to free the resource
	printf("command = %s\n", cmds_info->cmd_args[0]);
	exec(cmds_info->cmd_args, cmds_info->env);
}

int		wait_process(pid_t *pid_ary, int num_cmds)
{
	int		status;
	int		i;
	pid_t	check_pid;

//	printf(">%s\n", __func__);
	/*
	printf(" ==========\n");
	i = 0;
	while (i < num_cmds)
		printf(" pid[%d]\n", pid_ary[i++]);
	printf(" ==========\n");
	*/
	i = 0;
	wait(NULL);
	while (i < num_cmds)
	{
		waitpid(pid_ary[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
//		printf(" [%s | %s] status: %d\n", __func__, "WIFEXITED",  WEXITSTATUS(status));
		status = (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
//		printf(" [%s | %s] status: %d\n", __func__, "WIFSIGNALED", WTERMSIG(status));
		status = (WTERMSIG(status));
	}
	//else
//		printf(" not WIFEXITED nor WIFSIGNALED\n");
	return (status);
}

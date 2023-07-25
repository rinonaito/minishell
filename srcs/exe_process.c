/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/25 20:32:38 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>

extern int g_signal;

void	parent_process(int pipe_fd[2])
{
//	printf(">%s\n", __func__);

//	if (pipe_fd[WRITE_END] != STDOUT_FILENO)
//		close(pipe_fd[WRITE_END]);
	printf("IN PARENT\npipe_fd[READ_END] = [%d]\npipe_fd[WRITE_END] = [%d]\n", pipe_fd[READ_END], pipe_fd[WRITE_END]);
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
	{
		close(pipe_fd[READ_END]);
		ft_perror("dup2");
	}
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

	printf(">%s\n", __func__);
	printf("env = %p\n", env);
	//int i = -1;
	//while (env[++i])
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
	int ret =  execve(file, cmd_args, env);
	printf(" ret:[%d]\n", ret);
	printf(" file:[%s]\n", file);
	//if (execve(file, cmd_args, env) == -1)
		//ft_perror(" command not found");
}

//void	child_process(int fd[2], char **cmd_args, char **env, int num_cmds, int i)
void	child_process(int pipe_fd[2], t_cmds *cmds_info)
{
//	if (pipe_fd[READ_END] != STDIN_FILENO)
//	close(pipe_fd[READ_END]);
	printf("IN CHILD\npipe_fd[READ_END] = [%d]\npipe_fd[WRITE_END] = [%d]\n", pipe_fd[READ_END], pipe_fd[WRITE_END]);
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
	while (i < num_cmds)
	{
		waitpid(pid_ary[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
//		printf(" [%s | %s] status: %d\n", __func__, "WIFEXITED",  WEXITSTATUS(status));
		status = (WEXITSTATUS(status));
		g_signal = 0;
	}
	else if (WIFSIGNALED(status))
	{
		printf(" [%s | %s] status: %d\n", __func__, "WIFSIGNALED", WTERMSIG(status));
		status = 128 + (WTERMSIG(status));//128 + signal status
		g_signal = WTERMSIG(status);
	}
	//else
//		printf(" not WIFEXITED nor WIFSIGNALED\n");
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/18 17:01:07 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>

void	parent_process(int fd[2], int i, int num_cmds)
{
	printf(">%s\n", __func__);
	int		status;

	close(fd[WRITE_END]);
	//if (i != 1)//don't need this line
	{
		if (dup2(fd[READ_END], STDIN_FILENO) == -1)
		{
			close(fd[READ_END]);
			ft_perror("dup2\n");
		}
	}
	//close it to free the resource
	close(fd[READ_END]);
}

static void	exec(char **cmd_args, char **env)
{
	char	*file;

	printf(">%s\n", __func__);
	if (!cmd_args)
		return ;
	file = ft_search_path(cmd_args[0]);//get the path to the command
	//write(1, "stdout\n", 7);
	//write(2, "stderr\n", 7);
	if (!file)
	{
		ft_perror("path not found\n");
		return ;
	}
	else
		printf(" path found\n");
	printf(" file:[%s]\n", file);
	if (access(file, F_OK | X_OK) == 0)
	{
		printf(" access success\n");
		/*** print cmd_args ***/
		//int i = -1;
		//while (cmd_args[++i])
			//printf(" i:%d[%s]\n", i, cmd_args[i]);
		if (execve(file, cmd_args, env) == -1)
			ft_perror(" command not found\n");
	}
	else
	{
		ft_perror(" access failed\n");
	}
}

void	child_process(int fd[2], char **cmd_args, char **env, int num_cmds, int i)
{
	printf(">%s\n", __func__);
	close(fd[READ_END]);
	//i is the index of command starting from 1
	if (i < num_cmds)// - 1)
	{
		if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		{
			close(fd[WRITE_END]);
			ft_perror("dup2\n");
		}
	}
	else
		printf(" !(i < numcmds)\n");
	printf(" outside (should not be seen on the display unless !(i < numcmds))\n");
	close(fd[WRITE_END]);//close it to free the resource
	exec(cmd_args, env);
}

int		wait_process(pid_t *pid_ary, int num_cmds)//pid)//, int num_cmds)
{
	int		status;
	int		i;
	pid_t	check_pid;

	printf(">%s\n", __func__);
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
		printf(" [%s|%s] Exit: %d\n", __func__, "WIFEXITED",  WEXITSTATUS(status));
		status = (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf(" [%s|%s] Exit: %d\n", __func__, "WIFSIGNALED", WTERMSIG(status));
		status = (WTERMSIG(status));
	}
	else
		printf(" not WIFEXITED nor WIFSIGNALED\n");
	return (status);
}

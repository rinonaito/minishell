/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/20 21:13:20 by rnaito           ###   ########.fr       */
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
			ft_perror("dup2");
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
	if (execve(file, cmd_args, env) == -1)
		ft_perror(" command not found");
}

//void	child_process(int fd[2], char **cmd_args, char **env, int num_cmds, int i)
void	child_process(t_cmds *cmds_info)
{
	printf(">%s\n", __func__);
	close(fd[READ_END]);
	//i is the index of command starting from 1
	if (i < num_cmds)// - 1)
	{
		if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		{
			close(fd[WRITE_END]);
			ft_perror("dup2");
		}
	}
	close(fd[WRITE_END]);//close it to free the resource
	exec(cmd_args, env);
}

int		wait_process(pid_t *pid_ary, int num_cmds)
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
		printf(" [%s | %s] status: %d\n", __func__, "WIFEXITED",  WEXITSTATUS(status));
		status = (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf(" [%s | %s] status: %d\n", __func__, "WIFSIGNALED", WTERMSIG(status));
		status = (WTERMSIG(status));
	}
	else
		printf(" not WIFEXITED nor WIFSIGNALED\n");
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:42:52 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/16 17:26:39 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	"debug.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

void	ft_perror(char *message);

//void	exec(char **env, int i)
static void	exec(char **cmd_args, char **env)
{
	char	*file;

	printf(">%s\n", __func__);
	//if (!cmd_args)
		//return ;
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
		///*
		int i = 0;
		while (cmd_args[i])
		{
			printf(" i:%d[%s]\n", i, cmd_args[i]);
			i++;
		}
		//*/
		if (execve(file, cmd_args, env) == -1)
			ft_perror(" command not found\n");
			//printf(" command not found\n");
	}
	else
	{
		ft_perror(" access failed\n");
		//printf(" access failed\n");
	}
}

//void	child_process(int fd[2], char **cmd_args, char **env)
void	child_process(int fd[2], char **cmd_args, char **env, int num_cmds, int i)
{
	printf(">%s\n", __func__);
	printf(" ###%s###| i[%d], num_cmds[%d]\n", __func__, i, num_cmds);

	// read from fd[0]
		//dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	//dup2(fd[0], 0);
	//i is the index of command starting from 1
	if (i < num_cmds)// - 1)
	{
		//printf(" (i < numcmds)\n");
		//if (dup2(fd[READ_END], STDOUT_FILENO) == -1)
		if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		{
			close(fd[WRITE_END]);
			ft_perror("dup2\n");
		}
	}
	else
		printf(" !(i < numcmds)\n");
	printf(" outside (should not be seen on the display unless !(i < numcmds))\n");
	//close(fd[WRITE_END]);//why close
	exec(cmd_args, env);
}

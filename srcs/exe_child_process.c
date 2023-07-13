/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:42:52 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/13 22:11:17 by taaraki          ###   ########.fr       */
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
			printf(" command not found\n");
	}
	else
	{
		printf(" access failed\n");
	}
}

//void	child_process(int fd[2], char **cmd_args, char **env)
void	child_process(int fd[2], char **cmd_args, char **env, int num_cmds, int i)
{
	//extern char	**environ;
	//char		*argv[] = {"ls", "-l", NULL};

	printf(">%s\n", __func__);
	//printf("%s i:%d,num_cmds%d\n", __func__, i, num_cmds);
	close(fd[0]);
	//dup2(fd[0], 0);
	/*** TEST ***/
	//if the n_cmds is 1, no need to dup2 (fd[1],1)
	///*
	//if (i < num_cmds)
	//i is the index of command starting from 1
	if (i < num_cmds)// - 1)
	{
		if (dup2(fd[1], 1) == -1)
		{
			close(fd[1]);
			ft_perror("dup2\n");
		}
	}
	close(fd[1]);
	//execve("/bin/ls", cmd_args, env);
	//exec(env, i);
	exec(cmd_args, env);
	//printf("%s #end\n", __func__);
}

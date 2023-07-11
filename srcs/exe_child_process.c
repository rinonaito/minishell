/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:42:52 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/11 21:07:26 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

void	ft_perror(char *message);

//void	exec(char **env, int i)
void	exec(char **env)
{
	char	file[] = {"/bin/ls"};
	//char	*file[] = {"/bin/ls", "/usr/bin/wc", "/bin/cat"};
	char	*argv[] = {"ls", "-l", NULL};
	//char	*argv1[] = {"ls", "-l", NULL};
	//char	*argv2[] = {"wc", "-l", NULL};
	//char	*argv3[] = {"cat", NULL};
	//char	*argv[][3] = {{"ls", "-l", NULL}, {"wc", "-l", NULL}, {"cat", NULL}};
	int		d;

	printf("  %s\n", __func__);
	//printf("i:%d\n", i);
	if (access(file, F_OK | X_OK) == 0)
	{
		printf("  access success\n");
		//d = execve(file, argv, env);
		d = execve(file, argv, env);
		if (d == -1)
		{
			printf("  command not found\n");
		}
	}
	else
	{
		printf("  access failed\n");
	}
}

//void	child_process(int fd[2], char **cmd_args, char **env, int num_cmds, int i)
void	child_process(int fd[2], char **cmd_args, char **env)
{
	//extern char	**environ;
	//char		*argv[] = {"ls", "-l", NULL};

	printf("  %s #begin\n", __func__);
	//printf("%s i:%d,num_cmds%d\n", __func__, i, num_cmds);
	///*
	close(fd[0]);
	//dup2(fd[0], 0);
	/*** TEST ***/
	//if the n_cmds is 1, no need to dup2 (fd[1],1)
	/*
	//if (i < num_cmds - 1)
	{
		if (dup2(fd[1], 1) == -1)
		{
			close(fd[1]);
			ft_perror("dup2\n");
		}
	}
	close(fd[1]);
	*/
	//execve("/bin/ls", cmd_args, env);
	//exec(env, i);
	exec(env);
	//printf("%s #end\n", __func__);
}

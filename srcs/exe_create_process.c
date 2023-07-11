/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/12 04:11:42 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

/*
void	exec(char **env, int i);
void	ft_perror(char *message);
int	wait_process(int pid, int num_cmds);
void	child_process(int fd[2], char **cmd_args, char **env, int num_cmds, int i);
void	parent_process(int fd[2]);//, int i)
*/

//@func: create processes, including parent/child/wait processes
//@return_val:
//		 exit status of wait process		
int	create_process(char **cmd_args, char **env, int num_cmds, int i)
{
	int	fd[2];
	//int	i;
	pid_t	pid;
	int	status;

	//printf("%s\n", __func__);

	if (pipe(fd) == -1)
		ft_perror("pipe\n");
	pid = fork();
	printf("pid(create):%d\n", pid);
	if (pid == -1)
		ft_perror("fork\n");
	else if (pid == 0)
	{
		//printf("# child\n");
		child_process(fd, cmd_args, env, num_cmds, i);
	}
	else
	{
		//printf("# parent\n");
		parent_process(fd, i);
	}

	//wait(&status);
	//return (wait_process(pid, num_cmds));
	//return (1);
	return (pid);
}

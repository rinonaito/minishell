/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/15 16:44:06 by taaraki          ###   ########.fr       */
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
int	create_process(char **cmd_args, char **env, int num_cmds, int i, pid_t *pid_ary)
{
	int	fd[2];
	//int	i;
	pid_t	pid;
	int	status;

	//printf("%s\n", __func__);

	//pid_ary = malloc(sizeof(pid_t) * num_cmds);
	//if (!pid_ary)
		//return (0);
	if (pipe(fd) == -1)
		ft_perror("pipe\n");
	pid = fork();
	//printf("pid(create):%d\n", pid);
	if (pid == -1)
		ft_perror("fork\n");
	else if (pid == 0)
	{
		//if (is_builtin(cmd_args[0])
				//call_builtin(cmd_args);
		child_process(fd, cmd_args, env, num_cmds, i);
		printf("***return from child***\n");
	}
	else
	{
		pid_ary[i - 1] = pid;
		parent_process(fd, i, num_cmds);
	}

	//wait(&status);
	//return (wait_process(pid, num_cmds));
	return (pid);
}

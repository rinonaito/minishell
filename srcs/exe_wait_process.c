/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:31 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/15 22:53:17 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

int	wait_process(pid_t *pid_ary, int num_cmds)//pid)//, int num_cmds)
{
	int		status;
	int		i;
	pid_t	check_pid;


	printf(">%s\n", __func__);

	///*
	printf(" ==========\n");
	i = 0;
	while (i < num_cmds)
		printf(" pid[%d]\n", pid_ary[i++]);
	printf(" ==========\n");

	i = 0;
	//while (i++ < num_cmds)
	while (i < num_cmds)
	{
		waitpid(pid_ary[i], &status, 0);
		i++;//
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

	/*
	while ((check_pid = waitpid(-1, &status, 0)) > 0)
	{
		//check_pid = waitpid(-1, &status, 0);
		//wait(&status);
		printf(" check_pid:[%d]\n", check_pid);
		if (check_pid == pid)
		{
			printf(" check_pid == pid:[%d] status:%d\n", check_pid, status);
		    if (WIFEXITED(status))
			{
        		printf(" [%s] Exit: %d\n", __func__, WEXITSTATUS(status));
        		printf(" [%s] Exit: %d\n", __func__, status);
				return (WEXITSTATUS(status));
			}
		}
	}
	*/

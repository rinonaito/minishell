/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:31 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/14 02:01:45 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

int	wait_process(pid_t pid)//, int num_cmds)
{
	int		status;
	pid_t	check_pid;


	printf(">%s\n", __func__);
	printf(" ### before while ###\n");
	///*
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
	//*/

	/*
	while (i++ <= num_cmds)
	{
		waitpid(pid[i], &status, 0);
	}
	if (WIFEXITED(status))
	{
		printf(" [%s] Exit: %d\n", __func__, WEXITSTATUS(status));
		return (WEXITSTATUS(status));
	}
	else
		printf(" not WIFEXITED\n");
	*/

	//printf(" [%s] Exit: %d\n", __func__, status);
   //if (WIFEXITED(status))
   		//printf(" [%s] Exit: %d\n", __func__, WEXITSTATUS(status));
	printf(" ### after while ###\n");
	return (status);
}
/*
	int	status;
	int	i;

	//printf("%s\n", __func__);
	i = 0;
	while (i < num_cmds - 1)
	{
		wait(&status);
		i++;
	}
	waitpid(pid, &status, 0);
	return (status);
}
{
*/

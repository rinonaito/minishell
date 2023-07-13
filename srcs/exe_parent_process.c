/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:42 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/13 22:08:33 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

void	ft_perror(char *message);

void	parent_process(int fd[2], int i, int num_cmds)
{
	printf(">%s\n", __func__);
	int		status;
	int		tmp;

	close(fd[1]);
	tmp = dup(STDIN_FILENO);
	//printf(" tmp:%d\n", tmp);
	if (i != 0)
	{
		if (dup2(fd[0], 0) == -1)
		{
			close(fd[0]);
			ft_perror("dup2\n");
		}
	}
	printf(" ###%s###| i[%d], num_cmds[%d]\n", __func__, i, num_cmds);
	sleep(1);
	if (i == num_cmds)
	{
		dup2(tmp, STDIN_FILENO);	
	}

	//wait(&status);
	//if (WIFEXITED(status)) {
		//printf("Exit: %d\n", WEXITSTATUS(status));
	//}
}

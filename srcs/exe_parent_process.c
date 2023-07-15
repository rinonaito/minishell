/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:42 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/15 22:54:00 by taaraki          ###   ########.fr       */
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
	//int		tmp;

	close(fd[WRITE_END]);
	//tmp = dup(STDIN_FILENO);//@HERE
	//printf(" tmp:%d\n", tmp);
	if (i != 1)
	{
		if (dup2(fd[READ_END], STDIN_FILENO) == -1)
		{
			close(fd[READ_END]);
			ft_perror("dup2\n");
		}
	}
	close(fd[READ_END]);
	//printf(" ###%s###| i[%d], num_cmds[%d]\n", __func__, i, num_cmds);
	/*
	if (i == num_cmds)
	{
		dup2(tmp, STDIN_FILENO);	
		close(tmp);
	}
	*/
}

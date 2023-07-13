/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:42 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/12 06:29:01 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

void	ft_perror(char *message);

void	parent_process(int fd[2], int i)
{
	printf(">%s\n", __func__);
	int		status;

	close(fd[1]);
	if (i != 0)
	{
		if (dup2(fd[0], 0) == -1)
		{
			close(fd[0]);
			ft_perror("dup2\n");
		}
	}
	wait(&status);
	if (WIFEXITED(status)) {
		printf("Exit: %d\n", WEXITSTATUS(status));
	}
}

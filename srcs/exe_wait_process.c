/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:31 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/10 17:21:34 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

int	wait_process(int pid, int num_cmds)
{
	int	status;
	int	i;

	//printf("%s\n", __func__);
	i = 0;
///*
	while (i < num_cmds - 1)
	{
		wait(&status);
		i++;
	}
//*/
	waitpid(pid, &status, 0);
	return (status);
}

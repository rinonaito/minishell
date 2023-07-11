/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_new_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/11 20:28:25 by taaraki          ###   ########.fr       */
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

int	new_process(t_tree *root, char **env)
{
	int	fd[2];
	pid_t	pid;
	//char	***cmd_args = {{"ls", "-l", NULL}, {"wc", "-l", NULL}, {"cat", NULL}};
	char	*cmd_args[] = {"ls", "-l", NULL};
	int	status;


	printf("new_process: %s\n", root->param->token);
	
	//return (0);
	i = 0;
	//while (i < num_cmds)
	//{
		if (pipe(fd) == -1)
			ft_perror("pipe\n");
		pid = fork();
		if (pid == -1)
			ft_perror("fork\n");
		else if (pid == 0)
			child_process(fd, cmd_args, env);//, num_cmds, i);
		else
			parent_process(fd);
		//i++;
	//}	
	wait(&status);
	//return (wait_process(pid, num_cmds));
	return (1);
}

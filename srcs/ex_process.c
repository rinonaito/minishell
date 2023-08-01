/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/01 19:37:09 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<errno.h>

extern int	g_signal;

void	parent_process(int pipe_fd[2], t_cmds *cmds_info)
{
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
		ft_perror("dup2");
	close(pipe_fd[READ_END]);
}

static void	exec(char **cmd_args, char **env)
{
	char	*file;

	printf(">%s\n", __func__);
	//int i = -1;
	//hile (env[++i])
		//printf("env[%d]:[%s]\n", i, env[i]);
	if (!cmd_args)
		return ;
	file = ft_search_path(cmd_args[0]);//get the path to the command
	//if (access(file, F_OK | X_OK) == 0)
	//{
		//printf(" access success");
		//if (execve(file, cmd_args, env) == -1)
			//ft_perror(" command not found");
	//}
	//else
	//{
		//ft_perror(" access failed");
	//}
	printf(" file:[%s]\n", file);
	if (execve(file, cmd_args, env) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: command not found\n", cmd_args[0]);
		exit(127);//command not found -> 127
	}
}

void	child_process(int pipe_fd[2], t_cmds *cmds_info)
{
	printf("IN CHILD\npipe_fd[READ_END] = [%d]\npipe_fd[WRITE_END] = [%d]\n", pipe_fd[READ_END], pipe_fd[WRITE_END]);
	exec(cmds_info->cmd_args, cmds_info->env);
}

int		wait_process(pid_t *pid_ary, int num_cmds)
{
	int		status;
	int		i;
	pid_t	check_pid;

	i = 0;
	status = 0;
	while (i < num_cmds)
	{
		waitpid(pid_ary[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
		printf(" [%s] status: %d\n", "WIFEXITED",  WEXITSTATUS(status));
		status = (WEXITSTATUS(status));
		printf(" g_signal:[%d]\n", g_signal);
		g_signal = 0;
	}
	else if (WIFSIGNALED(status))
	{
		printf(" [%s] status: %d\n", "WIFSIGNALED", WTERMSIG(status));
		status = 128 + (WTERMSIG(status));//128 + signal status
		printf(" g_signal:[%d]\n", g_signal);
		g_signal = 0;
	}
	return (status);
}

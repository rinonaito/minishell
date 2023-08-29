/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/29 16:32:52 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<errno.h>

extern int	g_signal;

void	parent_process(int redir_fd[2], t_cmds *cmds_info, int pid)
{
	cmds_info->pid_ary[cmds_info->i - 1] = pid;
	if (cmds_info->i != cmds_info->num_cmds)
	{
		close (redir_fd[WRITE_END]);
		dup2(redir_fd[READ_END], STDIN_FILENO);
	}
}

static void	exec(char **cmd_args, char **env)
{
	char	*file;

	if (!cmd_args)
		return ;
	file = ft_search_path(cmd_args[0]);
	if (execve(file, cmd_args, env) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: command not found\n", cmd_args[0]);
		exit(127);
	}
}

void	child_process(int redir_fd[2], t_cmds *cmds_info)
{
	int	num;

	dup2(redir_fd[WRITE_END], STDOUT_FILENO); 
	if (redir_fd[READ_END] != STDIN_FILENO)
		dup2(redir_fd[READ_END], STDIN_FILENO); 
	if (is_builtin(cmds_info->cmd_args[0]))
	{
		num = call_builtin(cmds_info);
		exit(num);
	}
	else
		exec(cmds_info->cmd_args, cmds_info->env);
}

int		wait_process(pid_t *pid_ary, int num_cmds, int ret)
{
	int		status;
	int		i;

	i = 0;
	status = 0;
	while (i < num_cmds)
	{
		waitpid(pid_ary[i], &status, 0);
		i++;
	}
	if (ret != RET_UNSET)
		status = ret;
	else if (WIFEXITED(status))
	{
		status = (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		status = 128 + (WTERMSIG(status));
	}
	return (status);
}

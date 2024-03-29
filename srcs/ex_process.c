/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:43:25 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/10 23:38:06 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

extern int	g_signal;

void	parent_process(int pipe_fd [2], t_cmds *cmds_info, int pid)
{
	cmds_info->pid_ary[cmds_info->i - 1] = pid;
	if (cmds_info->i != cmds_info->num_cmds)
		dup2(pipe_fd[READ_END], STDIN_FILENO);
}

static void	exec(t_cmds *cmds_info)
{
	char		*file;
	struct stat	s;

	file = ft_search_path(cmds_info->cmd_args[0], cmds_info->env_lst);
	execve(file, cmds_info->cmd_args, cmds_info->env);
	stat(file, &s);
	if (ft_strequ(cmds_info->cmd_args[0], ".."))
		ft_printf_fd(2, "minishell: ..: %s\n", CMD_NF);
	else if (ft_strequ(cmds_info->cmd_args[0], "."))
	{
		ft_printf_fd(2, "minishell: .: %s", FILE_ARG);
		exit(2);
	}
	else if (S_ISDIR(s.st_mode))
		ft_printf_fd(2, "minishell: %s: %s\n", cmds_info->cmd_args[0], IS_DIR);
	else if (!ft_strchr(cmds_info->cmd_args[0], '/'))
		ft_printf_fd(2, "minishell: %s: %s\n", cmds_info->cmd_args[0], CMD_NF);
	else if (access(file, F_OK) == -1)
		ft_printf_fd(2, "minishell: %s: %s\n", cmds_info->cmd_args[0], NO_FILE);
	else if (access(file, X_OK) == -1)
	{
		ft_printf_fd(2, "minishell: %s: %s\n", cmds_info->cmd_args[0], NO_PER);
		exit(126);
	}
	exit(127);
}

void	child_process(int redir_fd[2], t_cmds *cmds_info)
{
	int	num;

	dup2(redir_fd[WRITE_END], STDOUT_FILENO);
	if (redir_fd[READ_END] != STDIN_FILENO)
		dup2(redir_fd[READ_END], STDIN_FILENO);
	if (is_builtin(cmds_info->cmd_args[0]))
	{
		num = call_builtin(cmds_info, 0, false);
		exit(num);
	}
	else
		exec(cmds_info);
}

int	wait_process(pid_t *pid_ary, int num_cmds, int ret)
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
	if (ret != RET_UNSET && status == 0)
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

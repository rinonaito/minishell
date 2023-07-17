/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_call_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:16:53 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/17 15:06:41 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	call_builtin(int fd[2], char **cmd_args, int j, int num_cmds)
{
	const char	*lst[] = {"echo", "cd", "pwd", "export", "unset", \
												"env", "exit", NULL};
	int			i;

	printf(">%s\n", __func__);
	if (!cmd_args || !cmd_args[0])
		return ;
	i = 0;
	while (lst[i])
	{
		if (ft_strnequ(lst[i], cmd_args[0]))
		{
			printf(" calling builin\n");
			built_in_process(fd, cmd_args, j, num_cmds);
			return ;
		}
		i++;
	}
	return ;
}

/*
void	built_in_process(int fd[2], char **cmd_args, int i, int num_cmds)
{
	int	tmp_fdout;	
	
	printf(">%s\n", __func__);
	tmp_fdout = dup(STDOUT_FILENO);//duplicate the fd of STDOUT

	close(fd[READ_END]);
	if (i < num_cmds)
	{
		printf(" (i < num_cmds)\n");
		if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		{
			close(fd[WRITE_END]);
			ft_perror("dup2");
		}
		//close(fd[WRITE_END]);
		//printf(" should not be seen on the screen\n");
	}
	else
	{
		printf(" !(i < num_cmds)\n");
	}

	printf(" ***should not be seen\n");
	close(fd[WRITE_END]);

	dup2(tmp_fdout, STDOUT_FILENO);//put back the fd of STDOUT
	close(tmp_fdout);

	printf(" ***actual built_in_process\n");
}
*/

void	built_in_process(int fd[2], char **cmd_args, int i, int num_cmds)
{
	printf(">%s\n", __func__);
	close(fd[READ_END]);
	//i is the index of command starting from 1
	if (i < num_cmds)// - 1)
	{
		if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		{
			close(fd[WRITE_END]);
			ft_perror("dup2\n");
		}
	}
	else
		printf(" !(i < numcmds)\n");
	printf(" outside (should not be seen on the display unless !(i < numcmds))\n");
	//close(fd[WRITE_END]);//why close
	printf(" ***actual built_in_process\n");
	exit(1);
}

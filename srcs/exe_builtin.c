/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:16:53 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/18 19:54:25 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//@func: check if a string is equal to one of the builtin commands
int	is_builtin(char *s)
{
	const char	*lst[] = {"echo", "cd", "pwd", "export", "unset", \
												"env", "exit", NULL};
	int			i;

	if (!s)
		return (0);
	i = 0;
	while (lst[i])
	{
		if (ft_strequ(lst[i], s))
			return (1);
		i++;
	}
	return (0);
}

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
		if (ft_strequ(lst[i], cmd_args[0]))
		{
			printf(" calling builin function : %s\n",lst[i]); 
			built_in_process(fd, cmd_args, j, num_cmds);
			return ;
		}
		i++;
	}
	return ;
}

void	built_in_process(int fd[2], char **cmd_args, int i, int num_cmds)
{
	printf(">%s\n", __func__);
	close(fd[READ_END]);
	if (i < num_cmds)//i is the index of command starting from 1
	{
		if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		{
			close(fd[WRITE_END]);
			ft_perror("dup2");
		}
	}
	//else
		//printf(" !(i < numcmds)\n");
	//printf(" outside (should not be seen on the display unless !(i < numcmds))\n");
	//close(fd[WRITE_END]);//why close
	//execute_builtin(cmd_args);
	{
		printf(" ***** %s *****\n", cmd_args[0]);
		if (builtin_echo(cmd_args) == 0)
			exit(0);
		else
			exit(1);
	}
}


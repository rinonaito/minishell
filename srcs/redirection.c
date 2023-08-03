/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:48:49 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/03 15:12:33 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static void	initialize(int *redir_fd, int *pipe_fd, t_cmds *cmds_info)
{
	if (cmds_info->i == cmds_info->num_cmds)
		redir_fd[WRITE_END] = STDOUT_FILENO;
	else
		redir_fd[WRITE_END] = pipe_fd[WRITE_END];
	if (cmds_info->i == 1)
		redir_fd[READ_END] = STDIN_FILENO;
	else
		redir_fd[READ_END] = pipe_fd[READ_END];
}

static int	set_redir_fd(t_token *param, int *redir_fd, t_cmds *cmds_info)
{
	int	have_cmd;

	have_cmd = 0;
	while (param != NULL && param->type != TK_PIPE)
	{
		if (param->type == TK_WORD)
		{
			have_cmd = 1;
			while (param != NULL && param->type == TK_WORD)
				param = param->next;
		}
		else
		{
			call_each_redir(redir_fd, param);
			param = param->next->next;
		}
	}
	return (have_cmd);
}

int	redirect(t_token *param, int *redir_fd, int *pipe_fd, t_cmds *cmds_info)
{
	int	have_cmd;

	initialize(redir_fd, pipe_fd, cmds_info);
	have_cmd = set_redir_fd(param, redir_fd, cmds_info);
	return (have_cmd);
}

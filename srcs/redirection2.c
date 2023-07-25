/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:48:49 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/25 15:24:11 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void		redirect_out_append(int *pipe_fd, t_token *param, int type)
{
	int			fd_out;
	char		*filename;

	filename = param->next->token;
	if (type == TK_REDIR_OUT)
		fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, OPEN_MODE);
	if (type == TK_APPEND)
	{
		fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, OPEN_MODE);
	}
	if (fd_out == -1)
		printf("open_error");
	if (pipe_fd[WRITE_END] != STDOUT_FILENO)
		close(pipe_fd[WRITE_END]);
	pipe_fd[WRITE_END] = fd_out;
}

void		redirect_in(int *pipe_fd, t_token *param)
{
	int		fd_in;
	char	*filename;

	filename = param->next->token;
	fd_in = open(filename, O_RDONLY);
	if (fd_in == -1)
		printf("open_error");
	close(pipe_fd[READ_END]);
	pipe_fd[READ_END] = fd_in;	
}

void		heredoc(int *pipe_fd, t_token *param)
{
	write(pipe_fd[READ_END], param->heredoc, ft_strlen(param->heredoc));
}

void	call_each_redir(int *pipe_fd, t_token *param)
{
	if (param->type == TK_REDIR_IN)
		redirect_in(pipe_fd, param);
	if (param->type == TK_REDIR_OUT)
		redirect_out_append(pipe_fd, param, TK_REDIR_OUT);
	if (param->type == TK_HEREDOC)
		heredoc(pipe_fd, param);
	if (param->type == TK_APPEND)
		redirect_out_append(pipe_fd, param, TK_APPEND);
}

int	redirect(t_token *param, int *pipe_fd, t_cmds *cmds_info)
{
	int	have_cmd;

	if (cmds_info->i == cmds_info->num_cmds)
	{
		close(pipe_fd[WRITE_END]);
		pipe_fd[WRITE_END] = STDOUT_FILENO;
	}
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
			call_each_redir(pipe_fd, param);
			param = param->next->next;
		}
	}
	return (have_cmd);
}

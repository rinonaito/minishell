/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:48:49 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/03 14:53:16 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	redirect_out_append(int *redir_fd, t_token *param, int type)
{
	int			fd_out;
	char		*filename;

	filename = param->next->token;
	if (type == TK_REDIR_OUT)
		fd_out = open(filename, O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, OPEN_MODE);
	if (type == TK_APPEND)
	{
		fd_out = open(filename, O_WRONLY | O_CREAT | O_CLOEXEC | O_APPEND, OPEN_MODE);
	}
//	printf("FD of [%s] : [%d]\n", filename, fd_out);
	if (fd_out == -1)
		ft_perror("bash");
	if (redir_fd[WRITE_END] != STDOUT_FILENO && redir_fd[WRITE_END] != fd_out)
	{
//		printf("close FD: [%d]\n", redir_fd[WRITE_END]);
		close(redir_fd[WRITE_END]);
	}
	redir_fd[WRITE_END] = fd_out;
}

void	redirect_in(int *redir_fd, t_token *param)
{
	int		fd_in;
	char	*filename;

	filename = param->next->token;
	fd_in = open(filename, O_RDWR | O_CLOEXEC);
	if (fd_in == -1)
		ft_perror("bash");
	if (redir_fd[READ_END] != STDIN_FILENO && redir_fd[READ_END] != fd_in)
	{
//		printf("close FD: [%d]\n", redir_fd[READ_END]);
		close(redir_fd[READ_END]);
	}
//	printf("FD of [%s] = [%d]\n", filename, fd_in);
	redir_fd[READ_END] = fd_in;
}

void	heredoc(int *redir_fd, t_token *param)
{
	int		fd_in;

//	printf("HEREDOC\n wiring in fd[%d]\n", redir_fd[READ_END]);
	fd_in = open("tempfile", O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, OPEN_MODE);
	if (fd_in == -1)
		ft_perror("bash");
	write(fd_in, param->heredoc, ft_strlen(param->heredoc));
	close (fd_in);
	fd_in = open("tempfile", O_RDONLY | O_CLOEXEC , OPEN_MODE);
	if (redir_fd[READ_END] != STDIN_FILENO && redir_fd[READ_END] != fd_in)
		close(redir_fd[READ_END]);
	printf("FD of tempfile = [%d]\n", fd_in);
	redir_fd[READ_END] = fd_in;
}

void	call_each_redir(int *redir_fd, t_token *param)
{
	if (param->type == TK_REDIR_IN)
		redirect_in(redir_fd, param);
	if (param->type == TK_REDIR_OUT)
		redirect_out_append(redir_fd, param, TK_REDIR_OUT);
	if (param->type == TK_HEREDOC)
		heredoc(redir_fd, param);
	if (param->type == TK_APPEND)
		redirect_out_append(redir_fd, param, TK_APPEND);
}

int	redirect(t_token *param, int *redir_fd, int *pipe_fd, t_cmds *cmds_info)
{
	int	have_cmd;

	if (cmds_info->i == cmds_info->num_cmds)
		redir_fd[WRITE_END] = STDOUT_FILENO;
	else
		redir_fd[WRITE_END] = pipe_fd[WRITE_END];
	if (cmds_info->i == 1)
		redir_fd[READ_END] = STDIN_FILENO;
	else
		redir_fd[READ_END] = pipe_fd[READ_END];
	have_cmd = 0;
	printf("<INITIALIZE>\nredir[READEND] = %d, redir[WRITE_END] = %d\n", redir_fd[READ_END], redir_fd[WRITE_END]);
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
	printf("<SET REDIR >\nredir[READEND] = %d, redir[WRITE_END] = %d\n", redir_fd[READ_END], redir_fd[WRITE_END]);
	return (have_cmd);
}

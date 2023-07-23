/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:48:49 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/23 18:10:47 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void		redirect_out_append(int *pipe_fd, t_token *param, int type)
{
	static	int fd_out;
//	static	int fd_in;
	char		*filename;

	fd_out = 1;
	filename = param->next->token;
	if (type == TK_REDIR_OUT)
	{
		printf("open as OUT\n");
		fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, OPEN_MODE);
		printf("fd_out : %d \n", fd_out);
	}
	if (type == TK_APPEND)
	{
		printf("open as APPEND\n");
		fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, OPEN_MODE);
	}
	pipe_fd[1] = fd_out;
//	pipe_fd[0] = fd_in;
}

void		redirect_in(int *pipe_fd, t_token *param)
{
	static	int fd_in;
//	static	int fd_out;
	char		*filename;

	//fd_out = 0;
	filename = param->next->token;
	fd_in = open(filename, O_RDONLY);
	pipe_fd[0] = fd_in;
//	pipe_fd[1] = fd_out;
}

//void		heredoc(int *pipe_fd, t_token *param)
//{
//	static	int fd_in;
////	static	int fd_out;
//	char		*filename;
//	char		*buf;
//
////	fd_out = 1;
//	filename = param->next->token;
//	fd_in = open(filename, O_RDONLY);
//	while (read())
//	pipe_fd[0] = fd_in;
////	pipe_fd[1] = fd_out;
//}

void	call_each_redir(int *pipe_fd, t_token *param)
{
	if (param->type == TK_REDIR_IN)
		redirect_in(pipe_fd, param);
	if (param->type == TK_REDIR_OUT)
		redirect_out_append(pipe_fd, param, TK_REDIR_OUT);
//	if (param->type == TK_HEREDOC)
//		heredoc(pipe_fd, param);
	if (param->type == TK_APPEND)
		redirect_out_append(pipe_fd, param, TK_APPEND);
}

pid_t	pipe_and_fork(t_token *param, int	*pipe_fd, int *have_cmd, t_cmds *cmds_info)
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		ft_perror("pipe\n");
	if (cmds_info->i == cmds_info->num_cmds)
		pipe_fd[WRITE_END] = STDOUT_FILENO;
	*have_cmd = 0;
	while (param != NULL && param->type != TK_PIPE)	
	{
		if (param->type == TK_WORD)
		{
			*have_cmd = 1;
			while (param != NULL && param->type == TK_WORD)
				param = param->next;
		}
		else
		{
			printf("before REDIR\n");
			call_each_redir(pipe_fd, param);
			param = param->next->next;
		}
	}
	if (*have_cmd == 1)
	{
		printf("FORK\n");
		pid = fork();
	}
	return (pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_each_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:00:26 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/04 13:35:43 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static void	redirect_out_append(int *redir_fd, t_token *param, int type)
{
	int			fd_out;
	char		*filename;

	filename = param->next->token;
	if (type == TK_REDIR_OUT)
		fd_out = open(filename, O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, OPEN_MODE);
	if (type == TK_APPEND)
		fd_out = open(filename, O_WRONLY | O_CREAT | O_CLOEXEC | O_APPEND, OPEN_MODE);
	if (fd_out == -1)
		ft_perror("bash");
//	if (redir_fd[WRITE_END] != STDOUT_FILENO)
//		close(redir_fd[WRITE_END]);
	redir_fd[WRITE_END] = fd_out;
}

static void	redirect_in(int *redir_fd, t_token *param)
{
	int		fd_in;
	char	*filename;

	filename = param->next->token;
	fd_in = open(filename, O_RDWR | O_CLOEXEC);
	if (fd_in == -1)
		ft_perror("bash");
//	if (redir_fd[READ_END] != STDIN_FILENO)
//		close(redir_fd[READ_END]);
	redir_fd[READ_END] = fd_in;
}

char	*generate_random_str(void)
{
	int		rand_fd;
	int		bytes_read;
	char	*filename;
	size_t	i;

	filename = malloc(sizeof(char) * 10);
	rand_fd = open("/dev/urandom", O_RDONLY);
	i = 0;
	while (i < 9)
	{
		read(rand_fd, &filename[i], 1);
		while (ft_isalnum(filename[i]) == 0)
			read(rand_fd, &filename[i], 1);
		i++;
	}
	filename[i] = '\0';
	if (open(filename, O_RDONLY) == -1)
		return (filename);
	free(filename);
	generate_random_str();
	return (NULL);
}

static char	*heredoc(int *redir_fd, t_token *param)
{
	int		fd_in;
	int		is_newname;
	char	*filename;

	filename = generate_random_str();
	fd_in = open(filename, O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, OPEN_MODE);
	if (fd_in == -1)
		ft_perror("bash");
	write(fd_in, param->heredoc, ft_strlen(param->heredoc));
	close (fd_in);
	fd_in = open(filename, O_RDONLY | O_CLOEXEC, OPEN_MODE);
	if (fd_in == -1)
		ft_perror("bash");
	redir_fd[READ_END] = fd_in;
	return (filename);
}

char	*call_each_redir(int *redir_fd, t_token *param)
{
	char	*filename;

	filename = NULL;
	if (param->type == TK_REDIR_IN)
		redirect_in(redir_fd, param);
	if (param->type == TK_REDIR_OUT)
		redirect_out_append(redir_fd, param, TK_REDIR_OUT);
	if (param->type == TK_HEREDOC)
		filename = heredoc(redir_fd, param);
	if (param->type == TK_APPEND)
		redirect_out_append(redir_fd, param, TK_APPEND);
	return (filename);
}

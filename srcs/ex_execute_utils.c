/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:56:00 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/27 19:09:45 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	without_child_process(t_cmds *cmds_info, int *redir_fd)
{
	int	original_in;
	int	original_out;
	int	ret;

	original_in = dup(STDIN_FILENO);
	original_out = dup(STDOUT_FILENO);
	dup2(redir_fd[READ_END], STDIN_FILENO);
	dup2(redir_fd[WRITE_END], STDOUT_FILENO);
	ret = call_builtin(cmds_info);
//	g_signal = ret;//temporarily setting this to avoid compile error with flag
	if (redir_fd[READ_END] != STDIN_FILENO)
		close(redir_fd[READ_END]);
	if (redir_fd[WRITE_END] != STDOUT_FILENO)
		close(redir_fd[WRITE_END]);
	dup2(original_in, STDIN_FILENO);
	dup2(original_out, STDOUT_FILENO);
}

void	with_child_process(t_cmds *cmds_info, int *redir_fd, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	ft_signal_child();
	if (pid == -1)
		ft_perror("fork\n");
	else if (pid == 0)
		child_process(redir_fd, cmds_info);
	else
		parent_process(pipe_fd, cmds_info, pid);
}

//@func: create processes, including parent/child/wait processes
//@return_val:
//		 exit status of wait process		
//static void	create_process(t_cmds *cmds_info, t_tree *root)
void	create_process(t_cmds *cmds_info, t_tree *root)
{
	int		pipe_fd[2];
	int		redir_fd[2];
	t_token	*param;
	int		have_cmd;

	if (pipe(pipe_fd) == -1)
		ft_perror("pipe\n");
	param = root->param;
	have_cmd = redirect(param, redir_fd, pipe_fd, cmds_info);
	if (is_builtin(cmds_info->cmd_args[0]) && cmds_info->num_cmds == 1)
		without_child_process(cmds_info, redir_fd);
	else if (have_cmd == 1)
		with_child_process(cmds_info, redir_fd, pipe_fd);
	unlink(cmds_info->heredoc_file);
	free(cmds_info->heredoc_file);
	cmds_info->heredoc_file = NULL;
}

//@func: count the number of commands
void	count_num_cmds(t_tree *root, int *i)
{
	if (!root)
		return ;
	count_num_cmds(root->l_leaf, i);
	if (root->type != TK_PIPE)
		*i += 1;
	count_num_cmds(root->r_leaf, i);
}

//@func: trace the tree structure and create processes
void	trace_inorder(t_tree *root, t_cmds *cmds_info)
{
	if (root == NULL)
		return ;
	trace_inorder(root->l_leaf, cmds_info);
	if (root->type != TK_PIPE)
	{
		cmds_info->i += 1;
		cmds_info->cmd_args = create_cmds(root);
		create_process(cmds_info, root);
		//cmds_info->cmd_args = free_args(cmds_info->cmd_args);
	}
	trace_inorder(root->r_leaf, cmds_info);
}

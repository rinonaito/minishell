/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:56:00 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/20 21:22:53 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//@func: create processes, including parent/child/wait processes
//@return_val:
//		 exit status of wait process		
static void	create_process(t_cmds *cmds_info)
{
	int	pipe_fd[2];
	pid_t	pid;

	//printf("%s\n", __func__);
	if (pipe(pipe_fd) == -1)
		ft_perror("pipe\n");
	pid = fork();
	if (pid == -1)
		ft_perror("fork\n");
	else if (pid == 0)
	{
		//execute builtin in child process
		if (is_builtin(cmds_info->cmd_args[0]))
		{
			call_builtin(pipe_fd, cmds_info);
		}
		else
			child_process(pipe_fd, cmds_info);
		printf(" *** return from child ***\n");
	}
	else
	{
		cmds_info->pid_ary[cmds_info->i - 1] = pid;
		parent_process(pipe_fd, cmds_info);
	}
}

/*
pid_t pipe_and_fork()
{
	if (pipe(pipe_fd) == -1)
		ft_perror("pipe\n");
	//parse
	// analyze the param
	while (param->type != TK_PIPE)	
	{
		if (is_redirect_in(param))
			redirect_in(fd);
		if (is_redirect_out(param))
			redirect_out(fd);
	}
	pid = fork();
	return (pid);
}

int		redirect_out(int fd[2])
{
	static	int fd_out;
	//static	int fd_out;
	fd_out = 1;
	fd_in = open("file_name");
	fd[1] = fd_out;
	//fd[0] = fd_in;
}

int		redirect_in(int fd[2])
{
	static	int fd_in;
	//static	int fd_out;
	fd_in = 0;
	fd_in = open("file_name");
	fd[0] = fd_in;
	//fd[1] = fd_out;
}
*/

//@func: count the number of commands
static void	count_num_cmds(t_tree *root, int *i)
{
	if (!root)
		return ;
	count_num_cmds(root->l_leaf, i);
	if (root->type != TK_PIPE)//root->param || 
		*i += 1;
	count_num_cmds(root->r_leaf, i);
}

//@func: trace the tree structure and create processes
static void	trace_inorder(t_tree *root, t_cmds *cmds_info)
{
	if (root == NULL)
		return ;
	trace_inorder(root->l_leaf, cmds_info);
	if (root->type != TK_PIPE)
	{
		cmds_info->i += 1;
		cmds_info->cmd_args = create_cmds(root);
		/*** FROM HERE ***/ 
		//does everything in the create_process
		// fork to create the child process even when the command is builtin
		// create_process no longer needs to return pid (it stores them in ary)
		create_process(cmds_info);
		/*** TO HERE ***/ 
		free_args(&cmds_info->cmd_args);//free cmd_args and setting NUL
	}
	trace_inorder(root->r_leaf, cmds_info);
}

void	trace_tree_entry(t_tree *root, char **env)
{
	t_cmds	cmds_info;
	int		tmp_fdin;

	cmds_info.num_cmds = 0;
	count_num_cmds(root, &(cmds_info.num_cmds));
	cmds_info.pid_ary = malloc(sizeof(pid_t) * cmds_info.num_cmds);
	if(!cmds_info.pid_ary)
		return ;
	tmp_fdin = dup(STDIN_FILENO);//save the file descriptor(fd) of STDIN
	cmds_info.i = 0;
	//trace the tree structure and create processes
	trace_inorder(root, &cmds_info);
	dup2(tmp_fdin, STDIN_FILENO);//set back the fd of STDIN
	close(tmp_fdin);
	/*** print process IDs***/
	//printf(" ==========\n");
	//int	i = 0;
	//while (i < num_cmds)
		//printf(" pid[%d]\n", pid_ary[i++]);
	//printf(" ==========\n");
	wait_process(cmds_info.pid_ary, cmds_info.num_cmds);
}


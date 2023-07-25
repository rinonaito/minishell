/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:56:00 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/25 17:53:23 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

extern int	g_signal;

//@func: create processes, including parent/child/wait processes
//@return_val:
//		 exit status of wait process		
static void	create_process(char **cmd_args, char **env, int num_cmds, int i, pid_t *pid_ary)
{
	int	pipe_fd[2];
	pid_t	pid;
	int	status;

	//printf("%s\n", __func__);
	if (pipe(pipe_fd) == -1)
		ft_perror("pipe\n");
	pid = fork();
	if (pid == -1)
		ft_perror("fork\n");
	else if (pid == 0)
	{
		/*** signal handling ***/
		//signal(SIGQUIT, SIG_IGN);//shouldn't ignore 
		ft_signal_child();	
		/*** signal handling ***/
		//execute builtin in child process
		if (is_builtin(cmd_args[0]))
		{
			call_builtin(pipe_fd, cmd_args, i, num_cmds);
		}
		else
			child_process(pipe_fd, cmd_args, env, num_cmds, i);
		printf(" *** return from child ***\n");
	}
	else
	{
		pid_ary[i - 1] = pid;
		parent_process(pipe_fd, i, num_cmds);
	}
}

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
static void	trace_inorder(t_tree *root, char **env, int num_cmds, int *j, pid_t *pid_ary)
{
	char	**cmd_args;

	if (root == NULL)
		return ;
	trace_inorder(root->l_leaf, env, num_cmds, j, pid_ary);
	if (root->type != TK_PIPE)
	{
		*j += 1;
		cmd_args = create_cmds(root);
		/*** FROM HERE ***/ 
		//does everything in the create_process
		// fork to create the child process even when the command is builtin
		// create_process no longer needs to return pid (it stores them in ary)
		create_process(cmd_args, env, num_cmds, *j, pid_ary);
		/*** TO HERE ***/ 
		free_args(&cmd_args);//free cmd_args and setting NUL
	}
	trace_inorder(root->r_leaf, env, num_cmds, j, pid_ary);
}

//void	trace_tree_entry(t_tree *root, char **env)
void	trace_tree_entry(t_tree *root, char **env, int *status)
{
	int		num_cmds;
	int		i;
	int		tmp_fdin;
	pid_t	*pid_ary;

	num_cmds = 0;
	count_num_cmds(root, &num_cmds);
	pid_ary = malloc(sizeof(pid_t) * num_cmds);
	if(!pid_ary)
		return ;
	tmp_fdin = dup(STDIN_FILENO);//save the file descriptor(fd) of STDIN
	i = 0;
	//trace the tree structure and create processes
	trace_inorder(root, env, num_cmds, &i, pid_ary);
	dup2(tmp_fdin, STDIN_FILENO);//set back the fd of STDIN
	close(tmp_fdin);
	/*** print process IDs***/
	//printf(" ==========\n");
	//int	i = 0;
	//while (i < num_cmds)
		//printf(" pid[%d]\n", pid_ary[i++]);
	//printf(" ==========\n");
	//g_signal = wait_process(pid_ary, num_cmds);
	*status = wait_process(pid_ary, num_cmds);
}

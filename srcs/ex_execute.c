/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:56:00 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/05 21:39:08 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_env	*trace_tree_entry(t_tree *root, char **env, int *status, t_env *env_lst)
{
	t_cmds	cmds_info;
	int		tmp_fdin;
	int		ret;

	cmds_info.num_cmds = 0;
	count_num_cmds(root, &(cmds_info.num_cmds));
	cmds_info.pid_ary = malloc(sizeof(pid_t) * cmds_info.num_cmds);
	if (!cmds_info.pid_ary)
		return (NULL);
	tmp_fdin = dup(STDIN_FILENO);
	cmds_info.i = 0;
	cmds_info.env = env;
	cmds_info.env_lst = env_lst;
	cmds_info.heredoc_files = NULL;
	cmds_info.have_cmd = false;
	ret = trace_inorder(root, &cmds_info, *status);
	unlink_temp_files(cmds_info.heredoc_files);
	dup2(tmp_fdin, STDIN_FILENO);
	close(tmp_fdin);
	*status = wait_process(cmds_info.pid_ary, cmds_info.num_cmds, ret);
	free (cmds_info.pid_ary);
	return (cmds_info.env_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:55:33 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/02 15:01:37 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	relative_path(char *path, char *buff_cwd)
{
	char	*full_path;
	char	*temp;
	int		ret;

	ft_memset(buff_cwd, '\0', PATH_MAX);
	if (!getcwd(buff_cwd, PATH_MAX))
		return (-1);
	full_path = ft_strjoin(buff_cwd, "/");
	temp = full_path;
	full_path = ft_strjoin(full_path, path);
	ret = chdir(full_path);
	free(temp);
	free(full_path);
	temp = NULL;
	full_path = NULL;
	return (ret);
}

static int	absolute_path(char *path)
{
	int		ret;

	ret = chdir(path);
	return (ret);
}

/**
 *	if (old)pwd does not exists in env, add it to env.
 *	otherwise, replace (old)pwd with a new one
 */
static int	update_env(t_cmds *cmds_info, char *buff_cwd, char *pwd)
{
	char	*key;
	char	*val;
	t_env	*node;

	ft_memset(buff_cwd, '\0', PATH_MAX);
	if (!getcwd(buff_cwd, PATH_MAX))
		return (-1);
	node = search_same_key(cmds_info->env_lst, pwd);
	val = ft_strdup(buff_cwd);
	if (node)
	{
		change_val(node, val);
		free(val);
		val = NULL;
	}
	else
	{
		key = ft_strdup(pwd);
		ft_lstadd_back_env(&cmds_info->env_lst, ft_lstnew_env(key, val));
	}
	return (0);
}

// cd srcs
// [0] [1]
/*** 1. if 2nd element is null, go to home directory ***/
/*** 2. if absolute path is given just call chdir() ***/
/*** 3. if relative path is given, strjoin cwd with path given ***/
/*** 4. store the cwd before calling chdir(), and renew the OLDPWD ***/
/*** 5. get the cwd after calling chdir(), and renew the PWD ***/
int	builtin_cd(t_cmds *cmds_info)
{
	char	**cmd_args;
	char	buff_cwd[PATH_MAX];
	int		ret;

	ft_memset(buff_cwd, '\0', PATH_MAX);
	getcwd(buff_cwd, PATH_MAX);
	cmd_args = cmds_info->cmd_args;
	if (!cmd_args)
		return (-1);
	update_env(cmds_info, buff_cwd, "OLDPWD");
	if (!cmd_args[1])
		ret = chdir(my_getenv("HOME", cmds_info->env_lst));
	else
	{
		if (cmd_args[1][0] == '/')
			ret = absolute_path(cmd_args[1]);
		else
			ret = relative_path(cmd_args[1], buff_cwd);
	}
	update_env(cmds_info, buff_cwd, "PWD");
	if (ret == -1)
		ft_printf_fd(STDERR_FILENO, "bash: %s: %s: %s\n", \
				cmd_args[0], strerror(errno), cmd_args[1]);
	return (ret);
}

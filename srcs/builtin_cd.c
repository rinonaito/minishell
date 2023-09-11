/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:55:33 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/11 00:21:23 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	relative_path(char *path, char *buff_cwd, t_cmds *cmds_info)
{
	char	*full_path;
	char	*temp;
	int		ret;
	bool	valid;

	valid = true;
	ft_memset(buff_cwd, '\0', PATH_MAX);
	if (!getcwd(buff_cwd, PATH_MAX) && (!ft_strlcpy(buff_cwd,
				my_getenv("PWD", cmds_info->env_lst), PATH_MAX)))
		valid = false;
	full_path = ft_strjoin(buff_cwd, "/");
	temp = full_path;
	full_path = ft_strjoin(full_path, path);
	free(temp);
	temp = full_path;
	full_path = parse_full_path(full_path);
	free(temp);
	if (valid && ft_strequ(full_path, ""))
	{
		free(full_path);
		full_path = ft_strdup("/");
	}
	ret = chdir(full_path);
	free(full_path);
	return (ret);
}

static int	absolute_path(char *path, char *buff_cwd, t_cmds *cmds_info)
{
	int		ret;
	char	*temp;
	bool	valid;

	valid = true;
	if (!getcwd(buff_cwd, PATH_MAX))
	{
		if (!my_getenv("PATH", cmds_info->env_lst))
			valid = false;
	}
	temp = parse_full_path(path);
	if (valid && ft_strequ(temp, ""))
	{
		free(temp);
		temp = ft_strdup("/");
	}
	ret = chdir(temp);
	free(temp);
	temp = NULL;
	return (ret);
}

/*
 * if (old)pwd does not exists in env, add it to env.
 * 	otherwise, replace (old)pwd with a new one
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
		change_val(node, val);
	else
	{
		key = ft_strdup(pwd);
		ft_lstadd_back_env(&cmds_info->env_lst, ft_lstnew_env(key, val));
	}
	return (0);
}

static int	cd_to_home(t_cmds *cmds_info)
{
	char	*home;
	int		ret;

	home = my_getenv("HOME", cmds_info->env_lst);
	ret = chdir(home);
	if (ret == -1)
	{
		if (!home)
			ft_printf_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
		else
			ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: %s\n",
				home, strerror(errno));
		ret = 1;
	}
	return (ret);
}

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
	update_env(cmds_info, buff_cwd, "OLDPWD");
	if (!cmd_args[1])
		return (cd_to_home(cmds_info));
	else
	{
		if (cmd_args[1][0] == '/')
			ret = absolute_path(cmd_args[1], buff_cwd, cmds_info);
		else
			ret = relative_path(cmd_args[1], buff_cwd, cmds_info);
	}
	update_env(cmds_info, buff_cwd, "PWD");
	if (ret == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: %s\n", cmd_args[1], strerror(errno));
		ret = 1;
	}
	return (ret);
}

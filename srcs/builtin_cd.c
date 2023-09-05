/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:55:33 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/05 22:30:51 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/*** ***/
//parse
// remove '.', and remove '..' along with the directory above
// 1.split path using ft_split
// 2.treat them as list
// 3.free the first split char array
// 4.if . is found, remove the current directory 
// 5.if .. is found next, remove the current directory
// 6.malloc to create a new string
/*** ***/
//* /Users/taaraki/../taaraki/Documents/../../
//* ../minishell_repo/.

static int	relative_path(char *path, char *buff_cwd, t_cmds *cmds_info)
{
	char	*full_path;
	char	*temp;
	int		ret;

	ft_memset(buff_cwd, '\0', PATH_MAX);
	//still needs to deal with the case when PWD is not set
	if (!getcwd(buff_cwd, PATH_MAX))
		ft_strlcpy(buff_cwd, my_getenv("PWD", cmds_info->env_lst), PATH_MAX);
	full_path = ft_strjoin(buff_cwd, "/");
	temp = full_path;
	full_path = ft_strjoin(full_path, path);
	free(temp);
	temp = full_path;
	full_path = parse_full_path(full_path);
	free(temp);
	ret = chdir(full_path);
	free(full_path);
	temp = NULL;
	full_path = NULL;
	return (ret);
}

static int	absolute_path(char *path)
{
	int		ret;

	ret = chdir(parse_full_path(path));
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
			ret = absolute_path(cmd_args[1]);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:55:33 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/31 23:24:12 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//#include	<unistd.h>

/*
typedef struct s_cmds{
	char	**cmd_args;
	char	**env;
	pid_t	*pid_ary;
	int		num_cmds;
	int		i;
}					t_cmds;
*/

static int		relative_path(char *path, char *buff_cwd)
{
	//char	buff_cwd[PATH_MAX];
	char	*full_path;
	int		ret;

	printf(" >%s\n", __func__);
	ft_memset(buff_cwd, '\0', PATH_MAX);
	if (!getcwd(buff_cwd, PATH_MAX)) //printf("buff_cwd:[%s]\n", buff_cwd);
		return (-1);
	full_path = ft_strjoin(buff_cwd, "/");
	full_path = ft_strjoin(full_path, path);
	//printf(" full_path:[%s]\n", full_path);
	ret = chdir(full_path);
	free(full_path);
	full_path = NULL;
	return (ret);
}

static int		absolute_path(char *path)
{
	int		ret;

	printf(" >%s\n", __func__);
	ret = chdir(path);
	return (ret);
}

static int	update_oldpwd(t_cmds *cmds_info, char *buff_cwd)
{
	//char	buff_cwd[PATH_MAX];
	char	*oldpwd;

	printf(" >%s\n", __func__);
	ft_memset(buff_cwd, '\0', PATH_MAX);
	if (!getcwd(buff_cwd, PATH_MAX))
		return (-1);
	oldpwd = ft_strjoin("OLDPWD=", buff_cwd);
	if (!oldpwd)
		return (-1);
	/*
		if oldpwd exists in env, add it to env
		otherwise, replace oldpwd with a new one
	*/ 
	//if (exits_env(oldpwd, cmds_info->env))
		//add_env(oldpwd, cmds_info);
	//else
		//replace_env(oldpwd, cmds_info);
	free(oldpwd);
	oldpwd = NULL;
	return (0);
	
}

// cd /path
// 0  1
/*** 1. if 2nd element is null, go to home directory ***/
/*** 2. if absolute path is given just call chdir() ***/
/*** 3. if relative path is given, strjoin cwd with path given ***/
/*** 4. store the cwd before calling chdir(), and renew the OLDPWD ***/
/*** (5.) get the cwd after calling chdir(), and renew the PWD ***/
int		builtin_cd(t_cmds *cmds_info)
{
	char	**cmd_args;
	char	buff_cwd[PATH_MAX];
	int		ret;

	//option 1. absolute path
	//option 2. relative path

	printf(" >%s\n", __func__);
	//ft_memset(buff_cwd, '\0', PATH_MAX);
	//getcwd(buff_cwd, PATH_MAX);
	//printf("buff_cwd:[%s]\n", buff_cwd);
	cmd_args = cmds_info->cmd_args;
	if (!cmd_args)
		return (-1);//error
	if (!cmd_args[1])
	{
		//update_oldpwd(cmds_info, buff_cwd);
		//go to the home directory
		char *home = getenv("HOME");//"/Users/taaraki";
		ret = chdir(home);
	}
	else
	{
		//update_oldpwd(cmds_info);
		if (ft_strncmp("/", cmd_args[1], 1) == 0)
			ret = absolute_path(cmd_args[1]);
		else
			ret = relative_path(cmd_args[1], buff_cwd);
	}
	if (ret == -1)
		ft_printf_fd(STDERR_FILENO, "bash: %s: %s: %s\n", cmd_args[0], strerror(errno), cmd_args[1]);
	//printf(" strerror:[%s]\n", strerror(errno));
	return (ret);
}

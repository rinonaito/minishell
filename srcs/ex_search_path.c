/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:33:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/03 22:37:12 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static void	ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	if (!dst)
		return ;
	while (src[i] != '\0' && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

//if absolute path
static char	*absolute_path(char *filename, char *value)
{
	filename_wo_command = ft_strndup(filename, length_of_commands);
	while (value != NULL)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end != NULL)
			ft_strncpy(path, value, end - value);
		else
			break ;
		//printf(" path1:[%s]\n", path);
		/*** ***/
		//if absolute path
		//if (ft_strequ(filename_wo_command, path))
		//{
			//if (access(filename, F_OK | X_OK) == 0)
				//return (ft_strdup(path));
		//}
		/*** ***/
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		//duplicated = NULL;
		if (access(path, F_OK | X_OK) == 0)
			return (ft_strdup(path));
		value = end + 1;
		//printf(" value:[%s]\n", value);
		//printf(" path2:[%s]\n", path);
	}
	return (NULL);
	if (ft_strequ(filename_wo_command, path))
	{
		if (access(filename, F_OK | X_OK) == 0)
		return (ft_strdup(path));
	}
	return (NULL);
}

//@func: get the path name in the form of "/path/cmd"
//@args:
//		 const char *filename: command name
//@return_val:
//		 path, if the command is found and can be to be accessed
//		 NULL, if the command is not found or cannot be accessed
char	*ft_search_path(const char *filename, t_env *env_lst)
{
	char	path[PATH_MAX];
	char	*value;
	//char	*duplicated;
	char	*end;
	//
	char	*filename_wo_command;

	printf(" >>%s\n", __func__);
	printf(" filename:[%s]\n", filename);
	value = my_getenv("PATH", env_lst);
	if (filename[0] == '/')
		return (absolute_path(filename, value));
	while (value != NULL)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end != NULL)
			ft_strncpy(path, value, end - value);
		else
			break ;
		//printf(" path1:[%s]\n", path);
		/*** ***/
		//if absolute path
		//if (ft_strequ(filename_wo_command, path))
		//{
			//if (access(filename, F_OK | X_OK) == 0)
				//return (ft_strdup(path));
		//}
		/*** ***/
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		//duplicated = NULL;
		if (access(path, F_OK | X_OK) == 0)
			return (ft_strdup(path));
		value = end + 1;
	}
	return (NULL);
}
		//if (access(path, F_OK | X_OK) == 0)
		//{
			//duplicated = ft_strdup(path);
			//return (duplicated);
		//}

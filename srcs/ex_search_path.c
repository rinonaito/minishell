/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:33:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/11 12:42:42 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static char	*exist_absolute_path(const char *filename)
{
	char	*full_path;

	full_path = parse_full_path((char *)filename);
	if (ft_strequ(full_path, ""))
	{
		free(full_path);
		full_path = ft_strdup("/");
	}
	if (access(full_path, F_OK) == 0)
		return (full_path);
	return (NULL);
}

static char	*exist_relative_path(const char *filename, t_env *env_lst)
{
	char	buff_cwd[PATH_MAX];
	char	*full_path;
	char	*temp;
	bool	valid;

	valid = true;
	ft_memset(buff_cwd, '\0', PATH_MAX);
	if (!getcwd(buff_cwd, PATH_MAX) && (!ft_strlcpy(buff_cwd,
				my_getenv("PWD", env_lst), PATH_MAX)))
		valid = false;
	full_path = ft_strjoin(buff_cwd, "/");
	temp = full_path;
	full_path = ft_strjoin(full_path, (char *)filename);
	free(temp);
	temp = full_path;
	full_path = parse_full_path(full_path);
	free(temp);
	if (valid && ft_strequ(full_path, ""))
	{
		free(full_path);
		full_path = ft_strdup("/");
	}
	if (access(full_path, F_OK) == 0)
		return (full_path);
	return (NULL);
}

static void	update_path(const char *filename, char *path,
	char *value, char *end)
{
	ft_strncpy(path, value, end - value);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, filename, PATH_MAX);
}

static char	*return_path(const char *file, t_env *env_lst)
{
	if (file[0] == '/')
		return (exist_absolute_path(file));
	else if (ft_strchr(file, '.') || ft_strchr(file, '/'))
		return (exist_relative_path(file, env_lst));
	return (NULL);
}

//@func: get the path name in the form of "/path/cmd"
//@args:
//		 const char *filename: command name
//@return_val:
//		 path, if the command is found and can be to be accessed
//		 NULL, if the command is not found or cannot be accessed
char	*ft_search_path(const char *file, t_env *env_lst)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = my_getenv("PATH", env_lst);
	if (file[0] == '/' || (ft_strchr(file, '.') || ft_strchr(file, '/')))
		return (return_path(file, env_lst));
	while (value != NULL)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end == NULL)
			break ;
		update_path(file, path, value, end);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_strdup(path));
		value = end + 1;
	}
	ft_bzero(path, PATH_MAX);
	end = ft_strchr(value, '\0');
	update_path(file, path, value, end);
	if (access(path, F_OK | X_OK) == 0)
		return (ft_strdup(path));
	return (NULL);
}

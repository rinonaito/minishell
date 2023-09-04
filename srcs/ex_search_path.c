/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:33:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/04 10:39:13 by taaraki          ###   ########.fr       */
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

static char	*exist_absolute_path(const char *filename)
{
	if (access(filename, F_OK | X_OK) == 0)
		return ((char *)filename);
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
	char	*end;

	value = my_getenv("PATH", env_lst);
	if (filename[0] == '/')
		return (exist_absolute_path(filename));
	while (value != NULL)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end != NULL)
			ft_strncpy(path, value, end - value);
		else
			break ;
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_strdup(path));
		value = end + 1;
	}
	return (NULL);
}

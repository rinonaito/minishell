/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:33:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/29 16:42:32 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void    ft_strncpy(char *dst, char *src, int n)
{
    int i;

    i = 0;
	if (!dst)
		return ;
    while (src[i] != '\0' && i < n)
    {
		//printf(" i:[%d],src:[%s]\n", i, &src[i]);
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

//@func: get the path name in the form of "/path/cmd"
//@args:
//		 const char *filename: command name
//@return_val:
//		 path, if the command is found and can be to be accessed
//		 NULL, if the command is not found or cannot be accessed
char    *ft_search_path(const char *filename, t_env *env_lst)
{
    char    path[PATH_MAX];
    char    *value;
    char    *duplicated;
    char    *end;

    value = my_getenv("PATH", env_lst);
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
        duplicated = NULL;
        if (access(path, F_OK | X_OK) == 0)
        {
            duplicated = ft_strdup(path);
            return (duplicated);
        }
        value = end + 1;
    }
    return (NULL);
}

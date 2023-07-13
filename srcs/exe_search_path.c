/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:33:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/13 21:11:20 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	"debug.h"

void    ft_strncpy(char *dst, char *src, int n)
{
    int i;

    i = 0;
    while (src != '\0' && i < n)
    {
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
char    *ft_search_path(const char *filename)
{
    char    path[PATH_MAX];//max length of path
    char    *value;
    char    *duplicated;
    char    *end;

    value = getenv("PATH");
    //printf("PATH_MAX: %d\n", PATH_MAX);
    while (value != NULL)
    {
        ft_bzero(path, PATH_MAX);
        end = ft_strchr(value, ':');
        //printf("end %s\n", end); STOP;
        if (end != NULL)
            ft_strncpy(path, value, end - value);
        else
            ft_strncpy(path, value, PATH_MAX);
        ft_strlcat(path, "/", PATH_MAX);
        ft_strlcat(path, filename, PATH_MAX);
        duplicated = NULL;
        if (access(path, X_OK) == 0)
        {
            duplicated = ft_strdup(path);
			printf(">%s, access ok\n", __func__);
            return (duplicated);
        }
        value = end + 1;//shift to the next character
    }
	printf(">%s, NULL returned\n", __func__);
    return (NULL);
}

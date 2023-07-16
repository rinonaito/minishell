/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:33:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/16 19:56:28 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
//#include	"debug.h"

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

//NOTE: 
//############################################	
//		THIS FUNCTION MIGHT CAUSE SEGV
//############################################	
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
    //printf(" PATH_MAX: %d\n", PATH_MAX);
    //printf(" PATH:[%s]\n", value);
	//int	i = 0;
    while (value != NULL)
    {
		//printf(" i[%d]\n", i++);
        ft_bzero(path, PATH_MAX);
        end = ft_strchr(value, ':');
        //printf("end %s\n", end); STOP;
		//printf(" $$$\n");
		//printf(" %s\n", value);
        if (end != NULL)
            ft_strncpy(path, value, end - value);
        else
            ft_strncpy(path, value, PATH_MAX);
		//printf(" @@@\n");
        ft_strlcat(path, "/", PATH_MAX);
		//printf(" @@@\n");
        ft_strlcat(path, filename, PATH_MAX);
		//printf(" @@@\n");
        duplicated = NULL;
        if (access(path, X_OK) == 0)
        {
            duplicated = ft_strdup(path);
			printf(">%s, access ok\n", __func__);
            return (duplicated);
        }
        value = end + 1;//shift to the next character
		//printf(" ###\n");
    }
	//ft_perror(">%s, NULL returned\n", __func__);
    return (NULL);
}

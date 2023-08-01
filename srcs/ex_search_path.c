/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:33:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/01 15:08:35 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
//#include	"debug.h"

void    ft_strncpy(char *dst, char *src, int n)
{
    int i;

    i = 0;
	if (!dst)
		return ;
    while (src != '\0' && i < n)
    {
		//printf(" i:[%d],src:[%s]\n", i, &src[i]);
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
	//printf("len(value)[%zu]\n", ft_strlen(value));
    //printf(" PATH:[%s]\n", value);
    while (value != NULL)
    {
        ft_bzero(path, PATH_MAX);
        end = ft_strchr(value, ':');
        //printf("end %s\n", end); //STOP;
        if (end != NULL)
            ft_strncpy(path, value, end - value);
        else
		{
			break ;//has to break here
            //ft_strncpy(path, value, PATH_MAX);
			//SEGV here (value is not null terminated)
		}
		ft_strlcat(path, "/", PATH_MAX);
        ft_strlcat(path, filename, PATH_MAX);
        duplicated = NULL;
        if (access(path, F_OK | X_OK) == 0)
        {
            duplicated = ft_strdup(path);
			printf(">%s, access ok\n", __func__);
            return (duplicated);
        }
        value = end + 1;//shift to the next character
    }
    return (NULL);
}

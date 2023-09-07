/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:14:11 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/07 22:05:14 by taaraki          ###   ########.fr       */
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

static void	ft_free_tab(char ***tab)
{
	int	i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
}

static char	*create_path(char *new_path, char **path_ary, int size)
{
	char	*temp;
	int		skip_cnt;

	skip_cnt = 0;
	while (size-- > 0)
	{
		if (ft_strequ(path_ary[size], ".."))
			skip_cnt++;
		else if (ft_strequ(path_ary[size], ".") || path_ary[size][0] == '\0')
			;
		else if (skip_cnt > 0)
			skip_cnt--;
		else
		{
			temp = new_path;
			new_path = ft_strjoin(path_ary[size], new_path);
			free(temp);
			temp = new_path;
			new_path = ft_strjoin("/", new_path);
			free(temp);
		}
	}
	return (new_path);
}

char	*parse_full_path(char *full_path)
{
	char	*new_path;
	char	**path_ary;
	int		size;

	path_ary = ft_split(full_path, '/');
	size = 0;
	while (path_ary[size])
		size++;
	new_path = ft_strdup("");
	new_path = create_path(new_path, path_ary, size);
	ft_free_tab(&path_ary);
	return (new_path);
}

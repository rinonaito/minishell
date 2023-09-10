/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:23:05 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/07 22:07:33 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	builtin_pwd(t_cmds *cmds_info)
{
	char	buff_cwd[PATH_MAX];

	ft_memset(buff_cwd, '\0', PATH_MAX);
	if (!getcwd(buff_cwd, PATH_MAX))
	{
		ft_strlcpy(buff_cwd, my_getenv("PWD", cmds_info->env_lst), PATH_MAX);
	}
	if (buff_cwd[0] == '\0')
		return (1);
	printf("%s\n", buff_cwd);
	return (0);
}

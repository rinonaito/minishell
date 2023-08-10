/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:23:05 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/10 15:25:02 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int		builtin_pwd(t_cmds *cmds_info)
{
	char	buff_cwd[PATH_MAX];
	
	printf(" >%s\n", __func__);
	if (!cmds_info)//adding this just to meet the compile requirements
		return (1);
	ft_memset(buff_cwd, '\0', PATH_MAX);
	if (!getcwd(buff_cwd, PATH_MAX))
		return (-1);
	printf("%s\n", buff_cwd);
	return (0);
}

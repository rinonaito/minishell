/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 21:28:36 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/16 18:21:04 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

//@func: free cmd_args used for executing commands
char	**free_args(char ***argv)
{
	char	**p;
	int		i;

	if (!argv)
		return (NULL);
	p = *argv;
	i = 0;
	while (p[i])
	{
		free(p[i]);
		p[i] = NULL;
		i++;
	}
	p = NULL;
	return (NULL);
}

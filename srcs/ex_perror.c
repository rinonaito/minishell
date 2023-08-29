/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:11:33 by taaraki           #+#    #+#             */
/*   Updated: 2023/08/29 16:09:41 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>

void	ft_perror(char *message)
{
	//printf("%s\n", __func__);
//	printf("errno:%d\n", errno);
	if (message)
		perror(message);
//	exit(255);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:14:23 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/27 17:15:18 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"utils.h"

int	ft_putstr_i(int fd, char *s)
{
	int	i;

	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		if (i == INT_MAX)
			return (i);
		i++;
	}	
	return (i);
}

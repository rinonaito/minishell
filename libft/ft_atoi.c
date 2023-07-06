/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:52:30 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/06 21:26:54 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static char	*skip_whitespaces(char *str)
{
	char	*p;

	p = str;
	while ((*p >= 9 && *p <= 13) || *p == 32)
		p++;
	return (p);
}

int	ft_atoi(const char *str)
{
	char				*p;
	int					sign;
	unsigned long long	x;

	p = skip_whitespaces((char *)str);
	if (*p == '-')
		sign = -1;
	else
		sign = 1;
	if (*p == '+' || *p == '-')
		p++;
	x = 0;
	while (ft_isdigit(*p))
	{
		if (sign == -1)
		{
			if (x > LONG_MAX / 10 || (x == LONG_MAX / 10 && (*p - '0') > 8))
				return (0);
		}
		else if (sign == 1)
			if (x > LONG_MAX / 10 || (x == LONG_MAX / 10 && (*p - '0') > 7))
				return (-1);
		x = (x * 10) + (*p++ - '0');
	}
	return ((int)(sign * x));
}

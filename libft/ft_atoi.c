/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 23:20:33 by rnaito            #+#    #+#             */
/*   Updated: 2023/04/06 23:20:58 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_convert_number(int *str, int sign, size_t size)
{
	size_t	a;
	long	total_number;

	a = 0;
	total_number = 0;
	while (a < size)
	{
		if (sign == 1)
			if (total_number > LONG_MAX / 10
				|| (total_number == LONG_MAX / 10 && str[a] > 7))
				return ((int)LONG_MAX);
		if (sign == -1)
			if (total_number > LONG_MIN / -10
				|| (total_number == LONG_MIN / -10 && str[a] > 8))
				return ((int)LONG_MIN);
		total_number = total_number * 10 + str[a];
		a ++;
	}
	if (sign == -1)
		total_number = -total_number;
	return ((int)total_number);
}

static int	ft_check_sign(const char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] == '+' || str[i + 1] == '-')
			return (0);
		else
		{
			if (str[i] == '-')
				return (-1);
			if (str[i] == '+')
				return (1);
		}
	}
	return (1);
}

static const char	*ft_skip_sp(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	return (&str[i]);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	j;
	int		number_array[100];
	int		sign;
	int		total_number;

	str = ft_skip_sp(str);
	sign = ft_check_sign(str);
	if (sign == 0)
		return (0);
	i = 0;
	while (str[i] == '+' || str[i] == '-')
		i ++;
	j = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number_array[j] = (str[i] - '0');
		i++;
		j++;
	}
	total_number = ft_convert_number(number_array, sign, j);
	return (total_number);
}

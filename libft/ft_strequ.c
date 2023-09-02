/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:39:46 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/01 14:41:43 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(const char *s1, const char *s2)
{
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1);
	if (len != ft_strlen(s2))
		return (0);
	if (ft_strncmp(s1, s2, len) == 0)
		return (1);
	return (0);
}

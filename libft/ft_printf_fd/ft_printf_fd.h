/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:02:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/27 17:32:10 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include	"utils/utils.h"
# include	<stdarg.h>
# include	<stddef.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<limits.h>

int	ft_printf_fd(int fd, const char *s, ...);

#endif

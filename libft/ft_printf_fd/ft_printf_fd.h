/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:39:04 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/03 17:39:06 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include	"utils/utils.h"
# include	<stdarg.h>
# include	<stddef.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<limits.h>

int	ft_printf_fd(int fd, const char *s, ...);

#endif

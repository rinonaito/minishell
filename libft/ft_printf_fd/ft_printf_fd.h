/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
=======
/*   ft_printf.h                                        :+:      :+:    :+:   */
>>>>>>> master
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:02:54 by taaraki           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/31 23:13:40 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H
=======
/*   Updated: 2023/07/27 17:32:10 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
>>>>>>> master

# include	"utils/utils.h"
# include	<stdarg.h>
# include	<stddef.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<limits.h>

int	ft_printf_fd(int fd, const char *s, ...);

#endif

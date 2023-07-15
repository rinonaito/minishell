/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:02:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/05/17 09:40:54 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//# include	"../libft_d/libft.h"
# include	"utils/utils.h"
# include	<stddef.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<unistd.h>
# include	<limits.h>
# include	<stdarg.h>

int	ft_printf(const char *s, ...);

#endif

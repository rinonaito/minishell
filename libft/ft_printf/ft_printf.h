/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:15:07 by rnaito            #+#    #+#             */
/*   Updated: 2023/02/26 19:36:58 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int		ft_printf(const char *fmt, ...);
int		ft_print_char(char c);
long	ft_print_str(char *str);
int		ft_print_ptr(uintptr_t p);
int		ft_print_decint(int nb);
int		ft_print_decuint(unsigned int nb);
int		ft_print_hexint(unsigned int nb, char *base);
size_t	ft_strlen(const char *str);

#endif

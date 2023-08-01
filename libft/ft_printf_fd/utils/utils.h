/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:02:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/27 17:17:43 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include	<stddef.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<unistd.h>
# include	<limits.h>

int	ft_print_address(int fd, unsigned long long x);

int	ft_print_hex_l(int fd, unsigned long long x);

int	ft_print_hex_u(int fd, unsigned long long x);

int	ft_putuint(int fd, unsigned int x);

int	ft_putnbr_i(int fd, int nb);

int	ft_putstr_i(int fd, char *s);

int	ft_putchar_i(int fd, char c);

#endif

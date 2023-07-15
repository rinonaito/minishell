/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:02:54 by taaraki           #+#    #+#             */
/*   Updated: 2023/04/18 11:45:55 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include	<stddef.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<unistd.h>
# include	<limits.h>

int	ft_print_address(unsigned long long x);

int	ft_print_hex(unsigned long long x);
//int	ft_print_hex(unsigned long long x, int *flags);

int	ft_print_hex_u(unsigned long long x);

int	ft_putuint(unsigned int x);

int	ft_putnbr_i(int nb);

int	ft_putstr_i(char *s);

int	ft_putchar_i(char c);

#endif

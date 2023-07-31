# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 17:51:48 by taaraki           #+#    #+#              #
#    Updated: 2023/07/27 17:25:58 by taaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = cc
CFLAGS = -Wall -Wextra -Werror

UTILS_D = ./utils/
UTILS_FILES =\
	ft_print_address.c\
	ft_print_hex_l.c\
	ft_print_hex_u.c\
	ft_putuint.c\
	ft_putnbr_i.c\
	ft_putchar_i.c\
	ft_putstr_i.c
#UTILS_FILES = ft_print_address.c ft_print_hex_l.c ft_print_hex_u.c ft_putuint.c ft_putnbr_fd.c ft_putchar_i.c ft_putstr_i.c

SRCS = ft_printf_fd.c $(addprefix $(UTILS_D), $(UTILS_FILES))
OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	ar r $@ $^

run: $(NAME)
	@rm -f a.out error.log
	@$(CC) main.c $< 2> error.log
	./a.out

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	clean fclean re all bonus run FORCE

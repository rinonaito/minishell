# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 09:58:20 by rnaito            #+#    #+#              #
#    Updated: 2023/02/26 17:51:15 by rnaito           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRCS	= ft_printf.c \
		  ft_print_char.c \
		  ft_print_str.c \
		  ft_print_ptr.c \
		  ft_print_decint.c \
		  ft_print_decuint.c \
		  ft_print_hexint.c \
		  ft_strlen.c

OBJS	= $(SRCS:.c=.o)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

$(NAME): $(OBJS)
	ar rc $@ $^

.PHONY: all
all:	$(NAME)

.PHONY: .c.o
.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean:	clean
	rm -f $(NAME)

.PHONY: re
re:		fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 23:45:39 by rnaito            #+#    #+#              #
#    Updated: 2023/07/27 17:42:24 by taaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME	= libft.a
SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c  \
	ft_substr.c ft_strjoin.c ft_strtrim.c \
	ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	ft_printf/ft_print_char.c \
	ft_printf/ft_print_decint.c \
	ft_printf/ft_print_decuint.c \
	ft_printf/ft_print_hexint.c \
	ft_printf/ft_print_ptr.c \
	ft_printf/ft_print_str.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_strlen.c \
	ft_printf_fd/ft_printf_fd.c\
    ft_printf_fd/utils/ft_print_address.c\
    ft_printf_fd/utils/ft_print_hex_l.c\
    ft_printf_fd/utils/ft_print_hex_u.c\
    ft_printf_fd/utils/ft_putuint.c\
    ft_printf_fd/utils/ft_putnbr_i.c\
    ft_printf_fd/utils/ft_putchar_i.c\
    ft_printf_fd/utils/ft_putstr_i.c
B_SRCS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		  ft_lstclear.c ft_lstiter.c ft_lstmap.c 
 
OBJS	= $(SRCS:.c=.o)

B_OBJS	= $(B_SRCS:.c=.o)

ifdef WITH_BONUS
	SRCS += $(B_SRCS)
	OBJS += $(B_OBJS)
endif

CC	= cc
CFLAGS	= -Wall -Wextra -Werror

$(NAME): $(OBJS)
	ar rc $@ $^

.PHONY: all
all: $(NAME)

.PHONY: .c.o
.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: bonus
bonus:
	make WITH_BONUS=1

.PHONY: clean
clean:
	rm -f $(OBJS) $(B_OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

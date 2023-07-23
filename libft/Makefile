# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 16:23:52 by taaraki           #+#    #+#              #
#    Updated: 2023/04/30 07:20:22 by taaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strlen.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memset.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memcmp.c ft_bzero.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCS_BONUS =ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
NAME = libft.a

ifdef	WITH_BONUS
	OBJS_SWITCH = $(OBJS_BONUS)
else
	OBJS_SWITCH = $(OBJS)
endif	

all: $(NAME)

$(NAME): $(OBJS_SWITCH)
	ar r    $(NAME) $(OBJS_SWITCH)

bonus:
	make WITH_BONUS=1

.c.o:
	$(CC) $(CFLAGS) -c  $<  -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	clean fclean re all bonus

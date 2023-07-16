# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 16:01:50 by rnaito            #+#    #+#              #
#    Updated: 2023/07/16 18:31:30 by taaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -Wall -Werror -Wextra

LIBS = -lreadline -L$(LIBFT_DIR) -lft

NAME_LIBFT = libft.a
LIBFT_DIR = libft/


#####################################
#          MANDATORY PART           #
#####################################
NAME = minishell
INCLUDES = -I $(SRCSDIR) -I $(LIBFT_DIR)
SRCSDIR = srcs/
SRCS =	main.c\
		tokenize.c\
		ft_get_token.c\
		list.c\
		ft_is_syntax_error.c\
		ft_make_syntax_tree.c\
		libft_plus.c\
		exe_execute.c\
		exe_process.c\
		exe_create_cmds.c\
		exe_search_path.c\
		exe_perror.c\
OBJSDIR = objs/
OBJS = $(SRCS:%.c=$(OBJSDIR)%.o)

vpath %.c $(SRCSDIR) $(SRCSDIR_BONUS)
vpath %.h $(SRCSDIR) $(SRCSDIR_BONUS)
vpath %.o $(OBJSDIR) $(OBJSDIR_BONUS) $(OBJSDIR_DEBUG)
vpath %.a $(LIBFT_DIR)

#####################################
#          MANDATORY PART           #
#####################################
all: $(NAME)
$(NAME): $(NAME_LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $@
$(OBJSDIR)%.o: %.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
$(NAME_LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	rm -rf $(OBJS) $(OBJS_BONUS) $(OBJS_DEBUG) $(OBJSDIR) $(OBJSDIR_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)
	rm -f $(NAME) $(NAME_BONUS) $(NAME_DEBUG)

re: fclean all

.PHONY: fclean all re clean

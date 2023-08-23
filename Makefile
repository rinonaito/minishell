# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 16:01:50 by rnaito            #+#    #+#              #
#    Updated: 2023/08/23 13:16:37 by rnaito           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBS = -lreadline -L$(LIBFT_DIR) -lft

NAME_LIBFT = libft.a
LIBFT_DIR = libft/

#####################################
#          MANDATORY PART           #
#####################################
NAME = minishell
INCLUDES = -I $(SRCSDIR) -I $(LIBFT_DIR)

RL_DIR = $(shell brew --prefix readline)
LIBS += -L$(RL_DIR)/lib
INCLUDES += -I$(RL_DIR)/include

SRCSDIR = srcs/
SRCS =	main.c\
		tokenize.c\
		get_token.c\
		get_token_utils.c\
		quotes_utils.c\
		get_heredoc_content.c\
		ft_make_syntax_tree.c\
		ft_replace_key_with_val.c\
		my_getenv.c\
		ft_split_expanded_token.c\
		make_env_list.c\
		make_token_list.c\
		make_token_list_utils.c\
		env_lst_utils.c\
		libft_plus.c\
		redirection.c\
		call_each_redir.c\
		signal.c\
		ex_execute.c\
		ex_process.c\
		ex_create_cmds.c\
		ex_search_path.c\
		ex_perror.c\
		expansion.c\
		builtin.c\
		builtin_pwd.c\
		builtin_cd.c\
		builtin_env.c\
		clear_env_lst.c\
		builtin_export.c\
		builtin_unset.c\
		builtin_echo.c
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
	@echo > ~/.inputrc set echo-control-characters off
$(OBJSDIR)%.o: %.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
$(NAME_LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS) $(OBJS_BONUS) $(OBJS_DEBUG) $(OBJSDIR) $(OBJSDIR_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(NAME_BONUS) $(NAME_DEBUG)

re: fclean all

.PHONY: fclean all re clean

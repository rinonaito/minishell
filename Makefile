# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 16:01:50 by rnaito            #+#    #+#              #
#    Updated: 2023/09/03 22:33:42 by taaraki          ###   ########.fr        #
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

RL_DIR = $(shell brew --prefix readline)
LIBS += -L$(RL_DIR)/lib
INCLUDES += -I$(RL_DIR)/include

SRCSDIR = srcs/
SRCS =	main.c\
		tkn_tokenize.c\
		tkn_get_token.c\
		tkn_get_token_utils.c\
		tkn_make_token_list.c\
		tkn_make_token_list_utils.c\
		tkn_make_syntax_tree.c\
		tkn_free_syntax_tree.c\
		env_my_getenv.c\
		env_make_list.c\
		env_make_list_utils.c\
		exp_expand_str.c\
		exp_expand_str_utils.c\
		exp_expand_list.c\
		exp_remove_quotes.c\
		exp_replace_key_with_val.c\
		exp_word_split.c\
		redir_redirection.c\
		redir_call_each_redirection.c\
		redir_get_heredoc_content.c\
		quotes_utils.c\
		signal_set.c\
		signal_handler.c\
		ex_execute.c\
		ex_execute_utils.c\
		ex_process.c\
		ex_create_cmds.c\
		ex_search_path.c\
		ft_perror.c\
		builtin.c\
		builtin_pwd.c\
		builtin_exit.c\
		builtin_cd.c\
		builtin_env.c\
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

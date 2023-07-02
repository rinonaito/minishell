/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:38:11 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/02 21:43:09 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // for printf
# include <string.h> // for strlen
# include <readline/readline.h> //for readline
# include <readline/history.h> //for add_history
# include <stdlib.h> //for free
# include "../libft/libft.h" //for split

typedef enum e_token_type {
	TK_HEAD,
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
}		t_token_type;

typedef struct s_token {
	char				*token;
	t_token_type		type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_tree {
	t_token_type	type;
	char			*command; //use if the type is WORD
	struct s_token	*param; // use if the type is WORD
	struct s_tree	*r_branch; //use if the type is PIPE
	struct s_tree	*l_branch; //use if the type is PIPE
}						t_tree;

//tokenize.c
t_token	*ft_tokenize(char *line);
int		ft_check_token_type(char *token);

//ft_get_token.c
char	*skip_space(char *line);
char	*ft_find_operator(char *start, char *end, int *not_closed);
char	*ft_start_with_operator(char *start);
char	*skip_to_closing_quote(char *str, int *is_error);
char	*ft_get_token(char **line, int *not_closed);

//list.c
t_token	*ft_lstnew_ms(char *token, int type);
t_token	*ft_lstlast_ms(t_token *node);
void	ft_lstadd_back_ms(t_token **head, t_token *new);
void	ft_lstclear_ms(t_token **head);

//libft_plus.c
char	*ft_strndup(char *str, size_t len);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strchrchr(char *str, char c1, char c2, int *not_closed);

//ft_is_syntaxerror.c
int		ft_is_syntaxerror(t_token *head);

//make_tree.c
t_tree	*make_tree(t_token *head);

#endif

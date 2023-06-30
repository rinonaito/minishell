/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:38:11 by rnaito            #+#    #+#             */
/*   Updated: 2023/06/30 13:05:27 by taaraki          ###   ########.fr       */
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

/*** data type definition ***/
typedef enum e_token_type {
	TK_WORD,
	TK_OPERATOR,
}		t_token_type;

typedef struct s_token {
	char				*token;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_tree {
	char				*token;
	t_token_type		type;
	struct s_tree		*right;
	struct s_tree		*left;
}						t_tree;

//tokenize.c
t_token	*ft_tokenize(char *line);
int		ft_check_token_type(char *token);

//ft_get_token.c
char	*skip_space(char *line);
char	*ft_find_operator(char *start, char *end);
char	*ft_start_with_metachar(char *start, char *end);
char	*ft_start_with_quote(char *start);
char	*ft_get_token(char **line);

//list.c
t_token	*ft_lstnew_ms(char *token, int type);
t_token	*ft_lstlast_ms(t_token *node);
void	ft_lstadd_back_ms(t_token **head, t_token *new);

//libft_plus.c
char	*ft_strchrchr(char *str, char c1, char c2);
char	*ft_strndup(char *str, size_t len);
int		ft_strcmp(char *str1, char *str2);

#endif
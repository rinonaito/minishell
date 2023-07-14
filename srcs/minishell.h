/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:38:11 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/14 23:23:04 by rnaito           ###   ########.fr       */
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
	t_token_type	type; // for all type
	struct s_token	*param; // for leaf 
	struct s_tree	*r_leaf; // for node
	struct s_tree	*l_leaf; // for node
}						t_tree;

//tokenize.c
t_token	*ft_tokenize(char *line, int *is_error);
void	ft_make_token_list(t_token **head, char *line);
void	ft_put_token_inlist(t_token **head, char *token);
int		ft_check_token_type(char *token);

//ft_get_token.c
char	*ft_skip_space(char *line);
char	*ft_find_operator(char *start, char *end);
char	*ft_start_with_operator(char *start);
char	*ft_skip_to_closing_quote(char *str);
char	*ft_get_token(char **line);

//list.c
t_token	*ft_lstnew_ms(char *token, int type);
t_token	*ft_lstlast_ms(t_token *node);
void	ft_lstadd_back_ms(t_token **head,
			t_token *new);
void	ft_lstdel(t_token **current_node);
void	ft_lstclear_ms(t_token **head);

//libft_plus.c
char	*ft_strndup(char *str, size_t len);
int		ft_strcmp(char *str1, char *str2);
char	*ft_find_endoftoken(char *str);
char	*ft_find_quote(char *str);

//ft_is_syntax_error.c
int		ft_is_syntax_error(t_token *head);

//ft_make_syntax_tree.c
void	ft_free_syntax_tree(t_tree *root);
t_tree	*ft_make_node(t_token **token);
void	ft_complete_node(t_tree **node, t_tree *right, t_tree *left);
t_tree	*ft_make_leaf(t_token **token);
t_tree	*ft_make_syntax_tree(t_token *head);

//ft_expand_env.c
char	*ft_check_quotes(char *old_start);
int		ft_find_env(t_tree *root, char *old_token);
int		ft_check_all_param(t_tree *root);
void	ft_expand_env(t_tree *root);

//ft_replace_env.c
char	*ft_get_key_of_env(char *token);
char	*ft_make_new_token(char *token, char *doller,
			char *before, char *after);
int		ft_replace_env(t_tree *root, char **token, char *doller);

//ft_split_expanded_token.c
int		ft_for_start(char *space_char, char *ifs, char **new, char *old);
int		ft_split_with_ifs(char *space_char, char **old, size_t *i, char *new);
void	ft_for_middle(char *space_char, char *ifs, char **new, char *old);
char	*ft_split_token(char *ifs, char *old);
void	ft_split_expanded_token(t_token *param);

//ft_delete_quotes.c
void	ft_delete_quotes(t_token *param);
char	*ft_get_token_sin_quotes(char *with_quotes);

#endif

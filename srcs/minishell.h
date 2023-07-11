/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:38:11 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/11 22:00:25 by taaraki          ###   ########.fr       */
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
	char			*command; // for leaf
	struct s_token	*param; // for leaf 
	struct s_tree	*r_leaf; // for node
	struct s_tree	*l_leaf; // for node
}						t_tree;

//tokenize.c
t_token	*ft_tokenize(char *line);
int		ft_make_token_list(t_token **head, char *line);
int		ft_check_token_type(char *token);

//ft_get_token.c
char	*ft_skip_space(char *line);
char	*ft_find_operator(char *start, char *end, int *not_closed);
char	*ft_start_with_operator(char *start);
char	*ft_skip_to_closing_quote(char *str, int *is_error);
char	*ft_get_token(char **line, int *not_closed);

//list.c
t_token	*ft_lstnew_ms(char *token, int type);
t_token	*ft_lstlast_ms(t_token *node);
void	ft_lstadd_back_ms(t_token **head, t_token *new);
void	ft_lstdel(t_token **current_node);
void	ft_lstclear_ms(t_token **head);

//libft_plus.c
char	*ft_strndup(char *str, size_t len);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strchrchr(char *str, char c1, char c2, int *not_closed);

//ft_is_syntax_error.c
int		ft_is_syntax_error(t_token *head);

//ft_make_syntax_tree.c
t_tree	*ft_make_node(t_token **token);
void	ft_complete_node(t_tree **node, t_tree *right, t_tree *left);
char	*ft_find_command(t_token *token);
t_tree	*ft_make_leaf(t_token **token);
t_tree	*ft_make_syntax_tree(t_token *head);

/*** EXECUTION ***/
//create_process.c
int create_process(t_tree *root, char **cmd_args, char **env);
//child_process.c
void    child_process(int fd[2], char **cmd_args, char **env);//, int num_cmds, int i);
//parent_process.c
void    parent_process(int fd[2]);//, int i)
//wait_process.c
int wait_process(int pid, int num_cmds);
//ft_perror.c
void    ft_perror(char *message);
//ft_free.c
void	ft_args(char ***argv);
//create_cmds.c
char    **create_cmds(t_tree *root);


#endif

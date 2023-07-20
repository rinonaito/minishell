/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:38:11 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/20 20:54:01 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // for printf
# include <string.h> // for strlen
//# include <sys/types.h> // for t_pid
# include <unistd.h> // for t_pid
# include <readline/readline.h> //for readline
# include <readline/history.h> //for add_history
# include <stdlib.h> //for free
# include <signal.h> //for signal
# include <errno.h> //for errno
# include "../libft/libft.h" //for split


# define READ_END (0)
# define WRITE_END (1)

# define STANDARD (0)
# define SYNTAX_ERR (1)
# define HEREDOC_MODE (2)

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
	char				*heredoc;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_tree {
	t_token_type	type; // for all type
	struct s_token	*param; // for leaf 
	struct s_tree	*r_leaf; // for node
	struct s_tree	*l_leaf; // for node
}						t_tree;

typedef struct s_cmds{
	char	**cmd_args;
	char	**env;
	pid_t	*pid_ary;
	int		num_cmds;
	int		i;
}					t_cmds;

/*** TOKENIZE ***/
//tokenize.c
t_token	*ft_tokenize(char *line, int *is_error);
int		ft_make_token_list(t_token **head, char *line);
int		ft_put_token_inlist(t_token **head, char *token);
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
void	ft_lstadd_back_ms(t_token **head, t_token *new);
void	ft_lstdel(t_token **current_node);
void	ft_lstclear_ms(t_token **head);

//libft_plus.c
char	*ft_strndup(char *str, size_t len);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strchrchr(char *str, char c1, char c2, int *not_closed);
int		ft_strequ(const char *s1, const char *s2);
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

/*** EXECUTION ***/
//execute.c
void    trace_tree_entry(t_tree *root, char **env);

//process.c
void    child_process(int fd[2], char **cmd_args, char **env, int num_cmds, int i);
void    parent_process(int fd[2], int i, int num_cmds);
int		wait_process(pid_t *pid_ary, int num_cmds);

//ft_perror.c
void    ft_perror(char *message);

//ft_free.c
char	**free_args(char ***argv);

//create_cmds.c
char    **create_cmds(t_tree *root);

//search_path.c
char    *ft_search_path(const char *filename);

//call_builtin.c
void	call_builtin(int fd[2], char **cmd_args, int j, int num_cmds);
void	built_in_process(int fd[2], char **cmd_args, int i, int num_cmds);

//is_built_in.c
int		is_builtin(char *s);

//echo.c
int    builtin_echo(char **args);//, t_minishell *m)

/*** EXPANSION ***/
//expansion.c
char	*ft_check_quotes(char *old_start);
char	*ft_expand_str(char *old_token);
void	ft_expand_list(t_token **param);

//ft_replace_key_with_val.c
int		ft_for_braced_env(char **start, char **end, char *doller);
void	ft_for_unbraced_env(char **start, char **end, char *doller);
char	*ft_get_key_of_env(char *token);
char	*ft_make_new_token(char *token, char *doller,
			char *before, char *after);
char	*ft_replace_key_with_val(char **old_token, char *doller);

//ft_split_expanded_token.c
int		ft_for_start(char *space_char, char *ifs, char **new, char *old);
int		ft_split_with_ifs(char *space_char, char **old, size_t *i, char *new);
void	ft_for_middle(char *space_char, char *ifs, char **new, char *old);
char	*ft_split_token(char *ifs, char *old);
void	ft_split_expanded_token(t_token *param);

//ft_delete_quotes.c
void	ft_delete_quotes(t_token *param);
char	*ft_get_token_sin_quotes(char *with_quotes);

//ft_get_heredoc_input.c
char	*ft_get_delimiter(t_token *head, int *is_quoted);
char	*ft_make_input_str(char *delimiter);
void	ft_for_unbraced_env(char **start, char **end, char *doller);
void	ft_get_heredoc_input(t_token *head);

#endif

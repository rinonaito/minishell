/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:38:11 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/17 17:39:35 by taaraki          ###   ########.fr       */
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


# define READ_END 0
# define WRITE_END 1

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
int		ft_strequ(const char *s1, const char *s2);

//ft_is_syntax_error.c
int		ft_is_syntax_error(t_token *head);

//ft_make_syntax_tree.c
t_tree	*ft_make_node(t_token **token);
void	ft_complete_node(t_tree **node, t_tree *right, t_tree *left);
char	*ft_find_command(t_token *token);
t_tree	*ft_make_leaf(t_token **token);
t_tree	*ft_make_syntax_tree(t_token *head);

/*** EXECUTION ***/
//execute.c
void    trace_tree_entry(t_tree *root, char **env);
//process.c
void    child_process(int fd[2], char **cmd_args, char **env, int num_cmds, int i);
void    parent_process(int fd[2], int i, int num_cmds);
int		wait_process(pid_t *pid_ary, int num_cmds);//pid)//, int num_cmds)

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

#endif

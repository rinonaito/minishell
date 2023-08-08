/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:38:11 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/08 16:38:38 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // for printf
# include <stdbool.h> // for bool
# include <string.h> // for strlen
//# include <sys/types.h> // for t_pid
# include <unistd.h> // for t_pid
# include <readline/readline.h> //for readline
# include <readline/history.h> //for add_history
# include <stdlib.h> //for free
# include <signal.h> //for signal
# include <errno.h> //for errno
# include <fcntl.h> //for open 
# include "../libft/libft.h" //for split

extern int g_signal;

# define READ_END (0)
# define WRITE_END (1)

# define STANDARD (0)
# define SYNTAX_ERR (1)
# define HEREDOC_MODE (2)

# define OPEN_MODE (0644)

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

typedef struct s_env {
	char			*key;
	char			*val;
	int			is_env;
	struct s_env	*next;
}						t_env;

typedef struct s_cmds{
	char	**cmd_args;
	char	**env;
	t_env	*env_lst;
	pid_t	*pid_ary;
	int		num_cmds;
	int		i;
	char	*heredoc_file;
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
void	trace_tree_entry(t_tree *root, char **env, int *status, t_env *env_lst);

//process.c
void	child_process(int redir_fd[2], t_cmds *cmds_info);
void	parent_process(int pipe_fd[2], t_cmds *cmds_info, int pid);
int		wait_process(pid_t *pid_ary, int num_cmds);

//ft_perror.c
void    ft_perror(char *message);

//ft_free.c
char	**free_args(char ***argv);

//create_cmds.c
char    **create_cmds(t_tree *root);

//search_path.c
char    *ft_search_path(const char *filename);

//builtin.c
int	is_builtin(char *s);
int	call_builtin(t_cmds *cmds_info);

/*** EXPANSION ***/
//expansion.c
char	*ft_get_token_sin_quotes(char *with_quotes);
char	*ft_delete_quotes(char *with_quotes);
char	*ft_check_quotes(char *old_start);
char	*ft_expand_str(char *old_token, int status, t_env *env_lst);
void	ft_expand_list(t_token **param, int status, t_env *env_lst);

//ft_replace_key_with_val.c
int		ft_for_braced_env(char **start, char **end, char *doller);
void	ft_for_unbraced_env(char **start, char **end, char *doller);
char	*ft_get_key_of_env(char *token, int *is_error);
char	*ft_make_new_token(char *token, char *doller,
			char *before, char *after);
char	*ft_replace_key_with_val(char **old_token, char *doller, int status, t_env *env_lst);

//ft_split_expanded_token.c
int		ft_for_start(char *space_char, char *ifs, char **new, char *old);
int		ft_split_with_ifs(char *space_char, char **old, size_t *i, char *new);
void	ft_for_middle(char *space_char, char *ifs, char **new, char *old);
char	*ft_split_token(char *ifs, char *old);
void	ft_split_expanded_token(t_token *param, t_env *env_lst);

//ft_get_heredoc_input.c
char	*ft_get_delimiter(t_token *head, int *is_quoted);
char	*ft_make_input_str(char *delimiter);
void	ft_for_unbraced_env(char **start, char **end, char *doller);
void	ft_get_heredoc_input(t_token *head, int status, t_env *env_lst);

/*** SIGNAL ***/
//signal.c
void	ft_signal(int *status);
void	ft_signal_child(void);

//redirection.c
int		redirect(t_token *param, int *redir_fd, int *pipe_fd, t_cmds *cmds_info);

//call_each_redir.c
char	*call_each_redir(int *redir_fd, t_token *param);

/*** BUILTINS ***/
int		builtin_echo(t_cmds *cmds_info);
int		builtin_cd(t_cmds *cmds_info);
int		builtin_pwd(t_cmds *cmds_info);
int		builtin_exit(t_cmds *cmds_info);


//make_env_lst.c
t_env	*ft_lstnew_env(char	*key, char *val, int is_env);
t_env	*ft_lstlast_env(t_env *head);
void	ft_lstadd_back_env(t_env **head, t_env *new);
char	*get_key(char *env, char **val_start);
char	*get_val(char *val_start);
t_env	*make_env_lst(char	**env);

int		builtin_env(t_cmds *cmds_info);
int	builtin_export(t_cmds *cmds_info);

void	clear_env_lst(t_env **lst);

char	*my_getenv(char *key, t_env *env_lst);

#endif

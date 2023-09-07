/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:38:11 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/07 18:31:07 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // for printf
# include <stdbool.h> // for bool
# include <string.h> // for strlen
# include <unistd.h> // for t_pid
# include <readline/readline.h> //for readline
# include <readline/history.h> //for add_history
# include <stdlib.h> //for free
# include <signal.h> //for signal
# include <errno.h> //for errno
# include <fcntl.h> //for open 
# include "../libft/libft.h" //for split

extern int	g_signal;

# define READ_END (0)
# define WRITE_END (1)

# define STANDARD (0)
# define HEREDOC_MODE (2)

# define OPEN_MODE (0644)

# define RET_UNSET (1000)

typedef enum e_token_type {
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_APPEND,
	TK_HEREDOC,
}		t_token_type;

typedef enum e_expand_mode {
	FOR_NORMAL,
	FOR_HEREDOC,
	FOR_D_QUOTED,	
}		t_expand_mode;

typedef struct s_token {
	char				*token;
	t_token_type		type;
	char				*heredoc;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_tree {
	t_token_type	type;
	struct s_token	*param;
	struct s_tree	*r_leaf;
	struct s_tree	*l_leaf;
}						t_tree;

typedef struct s_env {
	char			*key;
	char			*val;
	struct s_env	*next;
}						t_env;

typedef struct s_cmds{
	char			**cmd_args;
	char			**env;
	t_env			*env_lst;
	pid_t			*pid_ary;
	int				num_cmds;
	int				i;
	struct s_token	*heredoc_files;
	bool			have_cmd;
}					t_cmds;

/*** TOKENIZE ***/
//tkn_tokenize.c
t_token	*tokenize(char *line, int *is_heredoc, int *status);

//tkn_get_token.c
//char	*get_token(char **line);
char	*get_token(char **line, int *is_error);

//tkn_get_token_utils.c
char	*get_token_end(char *token_start);

//tkn_make_token_list.c
t_token	*make_token_list(char *line, int *have_heredoc);

//tkn_make_token_list_utils.c
int		get_token_type(char *token);
t_token	*ft_lstnew_token(char *token, int type);
t_token	*ft_lstlast_token(t_token *node);
void	ft_lstadd_back_token(t_token **head, t_token *new);
void	ft_lstclear_token(t_token **head);

//tkn_make_syntax_tree.c
t_tree	*make_syntax_tree(t_token *head);

//tkn_free_syntax_tree.c
void	free_syntax_tree(t_tree *root, t_token *head);

/*** EXPANSION ***/
//exp_expand_list.c
int		expand_list(t_token **param, int status, t_env *env_lst);

//exp_expand_str.c
char	*expand_str(char *old_token, int status, t_env *env_lst,
			int expand_mode);

//exp_remove_quotes.c
char	*remove_quotes(char *with_quotes);
char	*remove_quotes_if_needed(char *env_expanded, int expand_mode);

//exp_expand_str_utils.c
char	*get_key(char *doller);
char	*get_val(char *env_key, int exit_status, t_env *env_lst,
			int expand_mode);

//exp_replace_key_with_val_utils.c
char	*replace_key_with_val(char *old_token, char *doller,
			char *env_key, char *env_val);

//exp_word_split.c
int		ft_split_with_ifs(char *space_char, char **old, size_t *i, char *new);
char	*split_expanded_word(char *expanded, t_env *env_lst);

//quotes_utils.c
char	*skip_to_closing_quote(char *str);
char	*find_quote(char *str);

//libft_plus.c
char	*ft_strndup(char *str, size_t len);
char	*ft_strchrchr(char *str, char c1, char c2, int *not_closed);
int		ft_strequ(const char *s1, const char *s2);

/*** EXECUTION ***/
//ex_execute.c
t_env	*trace_tree_entry(t_tree *root, char **env, int *status,
			t_env *env_lst);

//ex_execute_utils.c
int		without_child_process(t_cmds *cmds_info, int *redir_fd, int status);
void	with_child_process(t_cmds *cmds_info, int *redir_fd, int *pipe_fd);
int		create_process(t_cmds *cmds_info, t_tree *root, int status);
void	count_num_cmds(t_tree *root, int *i);
int		trace_inorder(t_tree *root, t_cmds *cmds_info, int status);

//process.c
void	child_process(int redir_fd[2], t_cmds *cmds_info);
void	parent_process(int pipe_fd[2], t_cmds *cmds_info, int pid);
int		wait_process(pid_t *pid_ary, int num_cmds, int ret);

//ft_perror.c
void	ft_perror(char *message);

//ft_free.c
char	**free_args(char **argv);

//create_cmds.c
char	**create_cmds(t_tree *root);

//search_path.c
char	*ft_search_path(const char *filename, t_env *env_lst);

//builtin.c
int		is_builtin(char *s);
int		call_builtin(t_cmds *cmds_info, int status, bool without_child);

/*** SIGNAL ***/
//signal.c
void	ft_signal(void);
void	ft_signal_child(void);
void	ft_signal_heredoc(void);
void	signal_handler_int(int signum);
void	signal_handler_int_child(int signum);
void	signal_handler_quit_child(int signum);
void	signal_handler_int_heredoc(int signum);
void	*rl_quit(void);

/*** REDIRECTION ***/
//redir_redirection.c
int		redirect(t_token *param, int *redir_fd, int *pipe_fd,
			t_cmds *cmds_info);

//redir_call_each_redir.c
char	*call_each_redir(int *redir_fd, t_token *param, int *is_error);

//redir_get_heredoc_input.c
void	get_heredoc_content(t_token *head, int status, t_env *env_lst);

//redir_get_heredoc_input_utils.c
char	*get_delimiter(t_token *heredoc_token, int *is_quoted);
char	*join_heredoc_lines(char *joined_heredoc, char *new_input);
char	*read_from_heredoc(char *delimiter);
void	add_heredoc_to_token_list(t_token *head, char *input);
void	for_unquoted(char **heredoc_content, int exit_status, t_env *env_lst);

//redir_unlink_temo_files.c
void	unlink_temp_files(t_token *temp_files);

/*** BUILTINS ***/
int		builtin_echo(t_cmds *cmds_info);
int		builtin_cd(t_cmds *cmds_info);
char	*parse_full_path(char *full_path);
//int		builtin_pwd(void);
int	builtin_pwd(t_cmds *cmds_info);
void	builtin_exit(t_cmds *cmds_info, int status, bool without_child);
int		builtin_env(t_cmds *cmds_info);
int		builtin_export(t_cmds *cmds_info);
void	change_val(t_env *same_key_node, char *val);
int		builtin_unset(t_cmds *cmds_info);

/*** ENV VARIABLE ***/
//make_env_lst.c
t_env	*ft_lstnew_env(char	*key, char *val);
void	ft_lstadd_back_env(t_env **head, t_env *new);
t_env	*make_env_lst(char	**env);

//env_lst_utils.c
int		is_wrong_key_name(char *key);
t_env	*search_same_key(t_env *head, char *key);
char	*get_key_for_env_list(char *env, char **val_start);
char	*get_val_for_env_list(char *val_start);
void	clear_env_lst(t_env **lst);

//my_get_env.c
char	*my_getenv(char *key, t_env *env_lst);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:38:42 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/06 17:07:35 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "debug.h"

int	g_signal = 0;

//void	ft_strncpy(char *dst, char *src, int n)
//{
//	int	i;
//
//	i = 0;
//	while (src != '\0' && i < n)
//	{
//		dst[i] = src[i];
//		i++;
//	}
//	dst[i] = '\0';
//}

//char	*ft_search_path(const char *filename)
//{
//	char	path[PATH_MAX];
//	char 	*value;
//	char	*duplicated;
//	char	*end;
//
//	value = getenv("PATH");
//	while (value != NULL)
//	{
//		ft_bzero(path, PATH_MAX);
//		end	= ft_strchr(value, ':');
//		if (end != NULL)
//			ft_strncpy(path, value, end - value);
//		else
//			ft_strncpy(path, value, PATH_MAX);
//		ft_strlcat(path, "/", PATH_MAX);
//		ft_strlcat(path, filename, PATH_MAX);
//		duplicated = NULL;
//		if (access(path, X_OK) == 0)
//		{
//			duplicated = ft_strdup(path);
//			return (duplicated);
//		}
//		value = end + 1;//shift to the next character
//	}
//	return (NULL);
//}

//void	ft_interpret(char *line)
//{
//	extern char **environ;
//	pid_t		child_pid;
//	char 		*argv[] = {line, NULL};
//	int			wstatus;
//	char		*path;
//
//	path = ft_search_path(line);
//	child_pid = fork(); //strat a new process
//	if (child_pid < 0)
//		exit(0);
//	if (child_pid == 0) // in child process
//	{
//		printf("child\n");
//		execve(path, argv, environ);
//	}
//	else // in parent process
//	{
//		printf("parent\n");
//		wait(&wstatus);
//	}
//}

void	trace_param_inorder(t_tree *root, char **env)
{
	if (root == NULL)
		return ;
	trace_param_inorder(root->l_leaf, env);
	if (root != NULL && root->param != NULL)
//		printf("param =%s$\n", root->param->token);
	trace_param_inorder(root->r_leaf, env);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*head;
	t_tree	*root;
	int		mode;
	int		status;

	if (argc != 1)
		printf("argc != 1\n");
	argv[0] = NULL;
	rl_outstream = stderr;
	while (1)
	{
		/*** signal handling ***/
		ft_signal(&status);
//		printf(" g_signal  [%d]\n", g_signal);
//		printf(" status($?)[%d]\n", status);
		/*** signal handling ***/
		line = readline("\x1b[1;38;5;122mminishell🐣 \033[0m");
//		printf(" line[%s]\n", line);
		if (line == NULL)
		{
//			printf("line is null\n");
			free (line);
			break ;
		}
		if (strlen(line) != 0)
			add_history(line);
		mode = STANDARD;
		head = ft_tokenize(line, &mode);
		if (head == NULL && mode == SYNTAX_ERR)
		{
			printf("syntax error\n");
//			system ("leaks -q minishell");
			return (1);
		}
		if (mode == HEREDOC_MODE)
		{
			//ft_get_heredoc_input(head, mode);
			if (ft_get_heredoc_input(head, mode) == 1)
			{
				printf(" ft_get_heredoc_input(head, mode) == 1\n");
				free(line);
				line = NULL;
				continue ;
			}
		}
		if (head != NULL)
		{
			free(line);
			line = NULL;
			root = ft_make_syntax_tree(head);
			ft_expand_list(&head, mode);
			//trace_param_inorder(root, env);
			trace_tree_entry(root, env, &status);
//			printf(" status(main):[%d]\n", status);
//			ft_free_syntax_tree(root);
		}
		free(line);
		line = NULL;
		//sleep(2);
	//	system ("leaks -q minishell");
	}
	return (0);
}

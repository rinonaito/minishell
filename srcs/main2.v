/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:38:42 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/19 16:42:55 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "debug.h"

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

void	trace_param_inorder(t_tree *root)
{
	static int	i;

	if (root == NULL)
		return ;
	trace_param_inorder(root->l_leaf);
	if (root != NULL && root->param != NULL)
		printf("param =%s$\n", root->param->token);
	trace_param_inorder(root->r_leaf);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*head;
	t_tree	*root;
	int		status;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("\x1b[1;38;5;122mminishell🐣 \033[0m");
		printf(" line[%s]\n", line);
		if (line == NULL)
		{
			printf("line is null\n");
			free (line);
			break ;
		}
		if (strlen(line) != 0)
			add_history(line);
		status = STANDARD;
		head = ft_tokenize(line, &status);
		if (head == NULL && status == SYNTAX_ERR)
		{
			printf("syntax error\n");
//			system ("leaks -q minishell");
			return (1);
		}
		if (status == HEREDOC_MODE)
			ft_get_heredoc_input(head);
		if (head != NULL)
		{
			free(line);
			line = NULL;
			root = ft_make_syntax_tree(head);
			ft_expand_list(&head);
			trace_param_inorder(root);
//			trace_tree_entry(root, env);
//			ft_free_syntax_tree(root);
		}
		free(line);
		line = NULL;
		//sleep(2);
	//	system ("leaks -q minishell");
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:38:42 by rnaito            #+#    #+#             */
/*   Updated: 2023/07/12 04:28:26 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
//
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
//
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

//count the number of commands
int		count_num_cmds(t_tree *root)
{
	static int	i;

	if (!root)
		return (0);
	count_num_cmds(root->l_leaf);
	if (root->param && root->type != TK_PIPE)
		i++; //printf("index:%d\n", ++index);
	count_num_cmds(root->r_leaf);
	return (i);
}

int		trace_inorder(t_tree *root, char **env, int num_cmds)
{
	static int	i;
	char	**cmd_args;
	pid_t	pid;

	if (root == NULL)
		return (1);
	trace_inorder(root->l_leaf, env, num_cmds);
	if (root->type != TK_PIPE)
	{
		i++;
		cmd_args = create_cmds(root);
		if (root->param)
		{
			//create_process(root, cmd_args, env);
			pid = create_process(cmd_args, env, num_cmds, i);
			printf("pid(trace)[%d]:%d\n", i, pid);
		}
		else
			printf("root->param is null\n");
		//free_args(&cmd_args);
	}
	trace_inorder(root->r_leaf, env, num_cmds);
	//printf("pid(trace_last)[%d]:%d\n", i, pid);
	return (pid);
}

void	trace_tree_entry(t_tree *root, char **env)
{
	int		num_cmds;
	int		i;
	int		status;
	pid_t	pid;

	num_cmds = count_num_cmds(root);
	pid = trace_inorder(root, env, num_cmds);
	printf("pid(main):%d\n", pid);
	i = 0;
	while (i++ < num_cmds - 1)
		wait(&status);
	waitpid(pid, &status, 0);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*head;
	t_tree	*root;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("\x1b[1;38;5;122mminishell🐣 \033[0m");
		if (line == NULL)
		{
			free (line);
			break ;
		}
		if (strlen(line) != 0)
			add_history(line);
		head = ft_tokenize(line);
//		while (head != NULL)
//		{
//			printf("%s\n", head->token);
//			head = head->next;
//		}
		if (head != NULL)
		{
			free(line);
			root = ft_make_syntax_tree(head);
			trace_tree_entry(root, env);
//
			//root->num_cmds = count_num_cmds(root);
			//printf("num_cmds:%d\n", root->num_cmds);
//
//			while (root != NULL)
//			{
//				if (root->r_leaf != NULL)
//					printf("right = %s\n", root->r_leaf->command);
//				if (root->l_leaf != NULL)
//					printf("left = %s\n", root->l_leaf->command);
//				root = root->l_leaf;
//				printf("root = %p\n", root);
//			}
	//		while (head != NULL)
	//		{
	//			printf("%s, %d\n", head->token, head->type);
	//			head = head->next;
	//		}
	//		ft_interpret(line);
			//create_process(env);
		}
	//	system ("leaks -q minishell");
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:38:42 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/02 16:27:26 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "debug.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_token	*head;
	t_tree	*root;
	int		mode;
	int		status;
	t_env	*env_lst;

	test_malloc();
	/*
	if (argc != 1)
		printf("argc != 1\n");
	argv[0] = NULL;
	status = 0;
	env_lst = make_env_lst(env);
	while (1)
	{
		ft_signal();
		line = readline("\x1b[1;38;5;122mminishell🐣 \033[0m");
		if (line == NULL)
			break ;
		if (ft_strlen(line) != 0)
			add_history(line);
		if (g_signal == SIGINT)
			status = 1;
		mode = STANDARD;
		head = tokenize(line, &mode);
		free(line);
		if (head == NULL)
		{
			if (mode == SYNTAX_ERR)
				printf("syntax error\n");
			continue;
		}
		if (mode == HEREDOC_MODE)
		{
			if (get_heredoc_content(head, mode, env_lst) == 1)
			{
				status = 1;
				continue ;
			}
		}
		if (head != NULL)
		{
			root = make_syntax_tree(head);
			if (expand_list(&head, status, env_lst) != 0)
			{
				printf("syntax error\n");
				status = 1;
				continue ;
			}
			trace_tree_entry(root, env, &status, env_lst);
			free_syntax_tree(root, head);
		}
	}
	clear_env_lst(&env_lst);
	*/
	return (0);
}

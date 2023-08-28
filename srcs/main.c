/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:38:42 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/28 20:01:50 by rnaito           ###   ########.fr       */
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

	if (argc != 1)
		printf("argc != 1\n");
	argv[0] = NULL;
	rl_outstream = stderr;
	status = 0;
	env_lst = make_env_lst(env);
	clear_env_lst(&env_lst);
	while (1)
	{
		rl_event_hook = NULL;
		/*** signal handling ***/
		g_signal = 0;
		ft_signal();
		/*** signal handling ***/
		line = readline("\x1b[1;38;5;122mminishell🐣 \033[0m");
		if (line == NULL)
		{
			free (line);
			printf("before breaking\n");
			break ;
		}
		if (strlen(line) != 0)
			add_history(line);
		/*** ***/
		if (g_signal == SIGINT)
			status = 1;
		/*** ***/
//		printf(" status($?)[%d]\n", status);
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
//			printf(" status(main):[%d]\n", status);
			free_syntax_tree(root);
		}
//		printf(" g_signal  [%d]\n", g_signal);
		//sleep(2);
	//	system ("leaks -q minishell");
	}
	clear_env_lst(&env_lst);
	printf("AFTER READLINE RETURNS NULL\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:38:42 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/10 15:05:43 by rnaito           ###   ########.fr       */
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
			break ;
		}
		if (strlen(line) != 0)
			add_history(line);
		/*** ***/
		if (g_signal == SIGINT)
			status = 1;
		/*** ***/
		printf(" status($?)[%d]\n", status);
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
			if (ft_get_heredoc_input(head, mode, env_lst) == 1)
			{
				free(line);
				line = NULL;
				status = 1;
				continue ;
			}
		}
		if (head != NULL)
		{
			free(line);
			line = NULL;
			root = ft_make_syntax_tree(head);
			ft_expand_list(&head, mode, env_lst);
			trace_tree_entry(root, env, &status, env_lst);
//			printf(" status(main):[%d]\n", status);
//			ft_free_syntax_tree(root);
		}
		free(line);
		line = NULL;
		printf(" g_signal  [%d]\n", g_signal);
		//sleep(2);
	//	system ("leaks -q minishell");
	}
	return (0);
}

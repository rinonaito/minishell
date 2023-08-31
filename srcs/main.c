/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:38:42 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/31 19:16:58 by rnaito           ###   ########.fr       */
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
	int		have_heredoc;
	int		exit_status;
	t_env	*env_lst;

	if (argc != 1)
		printf("argc != 1\n");
	argv[0] = NULL;
	exit_status = 0;
	env_lst = make_env_lst(env);
	while (1)
	{
		ft_signal();
		line = readline("\x1b[1;38;5;122mminishell🐣 \033[0m");
		if (line == NULL)
			exit(1);
		if (ft_strlen(line) != 0)
			add_history(line);
		if (g_signal == SIGINT)
			exit_status = 1;
		have_heredoc = 0;
		head = tokenize(line, &have_heredoc, &exit_status);
		free(line);
		if (head == NULL)
			continue;
		if (have_heredoc)
			get_heredoc_content(head, exit_status, env_lst);
		root = make_syntax_tree(head);
		expand_list(&head, exit_status, env_lst);
		trace_tree_entry(root, env, &exit_status, env_lst);
		free_syntax_tree(root, head);
	}
	clear_env_lst(&env_lst);
	return (0);
}

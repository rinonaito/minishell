/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:21:02 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/10 19:56:12 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static t_env	*interpret_line(char *line, t_env *env_lst, int *exit_status,
			char **env)
{
	t_token	*head;
	t_tree	*root;
	int		have_heredoc;
	int		heredoc_killed;

	have_heredoc = 0;
	heredoc_killed = 0;
	head = tokenize(line, &have_heredoc, exit_status);
	free(line);
	if (head == NULL)
		return (env_lst);
	if (have_heredoc)
		heredoc_killed = get_heredoc_content(head, *exit_status, env_lst);
	if (heredoc_killed)
	{
		ft_lstclear_token(&head);
		return (env_lst);
	}
	root = make_syntax_tree(head);
	expand_list(&head, *exit_status, env_lst);
	env_lst = trace_tree_entry(root, env, exit_status, env_lst);
	free_syntax_tree(root, head);
	return (env_lst);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		exit_status;
	t_env	*env_lst;

	argc = 42;
	argv[0] = NULL;
	exit_status = 0;
	env_lst = make_env_lst(env);
	while (1)
	{
		ft_signal();
		line = readline("\x1b[1;38;5;122mminishell🐣 \033[0m");
		if (line == NULL)
			exit(0);
		if (ft_strlen(line) != 0)
			add_history(line);
		if (g_signal == SIGINT)
			exit_status = 1;
		env_lst = interpret_line(line, env_lst, &exit_status, env);
	}
	clear_env_lst(&env_lst);
	return (0);
}

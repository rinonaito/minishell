/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_get_heredoc_content.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:20:45 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/10 16:27:05 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_heredoc_content(t_token *head, int exit_status, t_env *env_lst)
{
	char	*delimiter;
	int		is_quoted;
	char	*heredoc_content;
	t_token	*tmp;
	int		heredoc_killed;

	tmp = head;
	heredoc_killed = 0;
	while (head != NULL)
	{
		is_quoted = 0;
		while (head != NULL && head->type != TK_HEREDOC)
			head = head->next;
		if (head == NULL)
			break ;
		delimiter = get_delimiter(head, &is_quoted);
		heredoc_content = read_from_heredoc(delimiter, &heredoc_killed);
		if (!is_quoted)
			for_unquoted(&heredoc_content, exit_status, env_lst);
		add_heredoc_to_token_list(head, heredoc_content);
		head = head->next;
		free (delimiter);
	}
	head = tmp;
	return (heredoc_killed);
}

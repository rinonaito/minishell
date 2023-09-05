/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_get_heredoc_content.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:20:45 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/04 21:05:35 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_heredoc_content(t_token *head, int exit_status, t_env *env_lst)
{
	char	*delimiter;
	int		is_quoted;
	char	*heredoc_content;
	t_token	*tmp;

	tmp = head;
	while (head != NULL)
	{
		is_quoted = 0;
		while (head != NULL && head->type != TK_HEREDOC)
			head = head->next;
		if (head == NULL)
			break ;
		delimiter = get_delimiter(head, &is_quoted);
		heredoc_content = read_from_heredoc(delimiter);
		if (!is_quoted)
			for_unquoted(&heredoc_content, exit_status, env_lst);
		add_heredoc_to_token_list(head, heredoc_content);
		head = head->next;
	}
	head = tmp;
	return ;
}

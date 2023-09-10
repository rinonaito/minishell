/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_get_heredoc_content_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:20:03 by rnaito            #+#    #+#             */
/*   Updated: 2023/09/10 16:01:23 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_delimiter(t_token *heredoc_token, int *is_quoted)
{
	char	*delimiter;
	char	*opening_quote;
	char	*closing_quote;
	char	*without_quotes;

	delimiter = NULL;
	opening_quote = NULL;
	closing_quote = NULL;
	if (heredoc_token->next != NULL)
		delimiter = heredoc_token->next->token;
	if (delimiter != NULL)
	{
		opening_quote = find_quote(delimiter);
		closing_quote = skip_to_closing_quote(opening_quote);
		if (closing_quote != NULL && opening_quote != closing_quote)
		{
			*is_quoted = 1;
			without_quotes = remove_quotes(delimiter);
			delimiter = NULL;
			return (without_quotes);
		}
	}
	return (ft_strndup(delimiter, ft_strlen(delimiter)));
}

char	*join_heredoc_lines(char *joined_heredoc, char *new_input)
{
	char	*input_with_nl;
	char	*tmp;

	input_with_nl = ft_strjoin(new_input, "\n\0");
	if (input_with_nl == NULL)
		ft_perror("malloc");
	tmp = joined_heredoc;
	joined_heredoc = ft_strjoin(joined_heredoc, input_with_nl);
	if (joined_heredoc == NULL)
		ft_perror("malloc");
	free (input_with_nl);
	free(tmp);
	return (joined_heredoc);
}

//char	*read_from_heredoc(char *delimiter)
char	*read_from_heredoc(char *delimiter, int *heredoc_killed)
{
	char	*heredoc_oneline;
	char	*heredoc_all;

	ft_signal_heredoc();
	heredoc_all = ft_calloc(1, sizeof(char));
	while (1)
	{
		if (g_signal == SIGINT)
		{
			*heredoc_killed = 1;
			return (heredoc_all);
		}
		heredoc_oneline = readline("\x1b[34m>> \x1b[39m");
		if (heredoc_oneline == NULL || ft_strequ(heredoc_oneline, delimiter))
		{
			free(heredoc_oneline);
			break ;
		}
		heredoc_all = join_heredoc_lines(heredoc_all, heredoc_oneline);
		free (heredoc_oneline);
	}
	return (heredoc_all);
}

void	add_heredoc_to_token_list(t_token *head, char *input)
{
	while (head->type != TK_HEREDOC)
		head = head->next;
	head->heredoc = input;
}

void	for_unquoted(char **heredoc_content, int exit_status, t_env *env_lst)
{
	char	*expanded_content;

	expanded_content = expand_str(*heredoc_content, exit_status, env_lst,
			FOR_HEREDOC);
	if (expanded_content != NULL)
		*heredoc_content = expanded_content;
}

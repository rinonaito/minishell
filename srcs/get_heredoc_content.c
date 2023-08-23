/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:20:45 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/23 13:18:26 by rnaito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_delimiter(t_token *head, int *is_quoted)
{
	char	*delimiter;
	char	*opening_quote;
	char	*closing_quote;

	delimiter = NULL;
	opening_quote = NULL;
	closing_quote = NULL;
	while (head != NULL && head->type != TK_HEREDOC)
		head = head->next;
	if (head->next != NULL)
		delimiter = head->next->token;
	if (delimiter != NULL)
	{
		opening_quote = find_quote(delimiter);
		closing_quote = skip_to_closing_quote(opening_quote);
		if (closing_quote != NULL && opening_quote != closing_quote)
		{
			*is_quoted = 1;
			return (ft_get_token_sin_quotes(delimiter));
		}
	}
	return (delimiter);
}

static char	*join_heredoc_lines(char *joined_heredoc, char *new_input)
{
	char	*input_with_nl;
	char	*tmp;
	bool	is_first_line;
	
	if (ft_strlen(joined_heredoc) == 0)
		is_first_line = true;
	else
		is_first_line = false;
	input_with_nl = ft_strjoin(new_input, "\n");
	tmp = joined_heredoc;
	joined_heredoc = ft_strjoin(joined_heredoc, input_with_nl);
	if (!is_first_line)
		free(tmp);
	return (joined_heredoc);
}

static char	*read_from_heredoc(char *delimiter)
{
	char	*heredoc_oneline;
	char	*heredoc_all;

	/*** ***/
	ft_signal_heredoc();
	rl_event_hook = (rl_hook_func_t *)rl_quit;
	rl_done = 0;
	/*** ***/
	heredoc_all = "\0";
	while (1)
	{
		//printf(" rl_done:[%d], g_signal:[%d]\n", rl_done, g_signal);
		if (g_signal == SIGINT)
			return (NULL);
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

static void	add_heredoc_to_token_list(t_token *head, char *input)
{
	while (head->type != TK_HEREDOC)
		head = head->next;
	head -> heredoc = input;
}

int	get_heredoc_content(t_token *head, int status, t_env *env_lst)
{
	char	*delimiter;
	int		is_quoted;
	char	*heredoc_content;
	char	*expanded_content;

	is_quoted = 0;
	delimiter = get_delimiter(head, &is_quoted);
	heredoc_content = read_from_heredoc(delimiter);
	if (!heredoc_content)
		return (1);
	if (!is_quoted)
	{
		expanded_content = ft_expand_str(heredoc_content, status, env_lst);
		if (expanded_content != NULL)
			heredoc_content = expanded_content;
	}
	add_heredoc_to_token_list(head, heredoc_content);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_heredoc_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnaito <rnaito@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:29:01 by rnaito            #+#    #+#             */
/*   Updated: 2023/08/06 20:10:57 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_delimiter(t_token *head, int *is_quoted)
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
		opening_quote = ft_find_quote(delimiter);
		closing_quote = ft_skip_to_closing_quote(opening_quote);
		if (closing_quote != NULL && opening_quote != closing_quote)
		{
			*is_quoted = 1;
			return (ft_get_token_sin_quotes(delimiter));
		}
	}
	return (delimiter);
}

char	*ft_make_input_str(char *delimiter)
{
	char	*line;
	char	*with_nl;
	char	*input;
	char	*joined;

	//g_signal = 0;//do this in main
	/*** ***/
	ft_signal_heredoc();
	rl_event_hook = (rl_hook_func_t *)rl_quit;
	rl_done = 0;
	/*** ***/
	input = "\0";
	while (1)
	{
		//printf(" rl_done:[%d], g_signal:[%d]\n", rl_done, g_signal);
		if (g_signal == SIGINT)
			return (NULL);
		line = readline("\x1b[34m>> \x1b[39m");
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		with_nl = ft_strjoin(line, "\n");
		joined = ft_strjoin(input, with_nl);
		input = joined;
		free (line);
	}
	return (input);
}

void	ft_add_input_to_list(t_token *head, char *input)
{
	while (head->type != TK_HEREDOC)
		head = head->next;
	head -> heredoc = input;
}

//return_val:
//		0: if there's no problem
//		1: if the readline is stopped by signal
int	ft_get_heredoc_input(t_token *head, int status)
{
	char	*delimiter;
	int		is_quoted;
	char	*input;
	char	*new_input;

	is_quoted = 0;
	delimiter = ft_get_delimiter(head, &is_quoted);
	input = ft_make_input_str(delimiter);
	/*** ***/
	if (!input)
		return (1);
	/*** ***/
	if (is_quoted == 0)
	{
		new_input = ft_expand_str(input, status);
		if (new_input != NULL)
			input = new_input;
	}
	ft_add_input_to_list(head, input);
	return (0);
}

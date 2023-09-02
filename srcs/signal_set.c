/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:59:38 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/31 23:36:54 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

extern int	g_signal;

void	ft_signal(void)
{
	rl_event_hook = NULL;
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_int);
}

void	ft_signal_child(void)
{
	signal(SIGQUIT, signal_handler_quit_child);
	signal(SIGINT, signal_handler_int_child);
}

void	ft_signal_heredoc(void)
{
	rl_event_hook = (rl_hook_func_t *)rl_quit;
	rl_done = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_int_heredoc);
}

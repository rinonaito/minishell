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

void	signal_handler_int(int signum)
{
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);//write out the new line to STDERR
		rl_replace_line("", 0);//replace the line with empty string
		rl_on_new_line();//display a new prompt at the right position
		rl_redisplay();//redisplay the prompt
		g_signal = SIGINT;
	}
}

void	signal_handler_int_child(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		write(STDERR_FILENO, "\n", 1);//write out the new line to STDERR
	}
}

void	signal_handler_quit_child(int signum)
{
	if (signum == SIGQUIT)
	{
		g_signal = SIGQUIT;
		ft_printf_fd(STDERR_FILENO, "Quit: %d\n", g_signal);
	}
}

void	signal_handler_int_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		rl_done = 1;
	}
}

void	*rl_quit(void)
{
	if (g_signal == SIGINT)
	{
		rl_done = 1;
		//printf(" >%s, rl_done:[%d], g_signal:[%d]\n", __func__, rl_done, g_signal);
	}
	return (NULL);
}

void	ft_signal(int *status)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_int);

	if (g_signal == 1)
		*status = 1;
}

void	ft_signal_child(void)
{
	signal(SIGQUIT, signal_handler_quit_child);
	signal(SIGINT, signal_handler_int_child);
}

void	ft_signal_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_int_heredoc);
}

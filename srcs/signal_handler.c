/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <taaraki@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:59:38 by taaraki           #+#    #+#             */
/*   Updated: 2023/09/02 15:11:30 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

extern int	g_signal;

/*
	write(STDERR_FILENO, "\n", 1);//write out the new line to STDERR
	rl_replace_line("", 0);//replace the line with empty string
	rl_on_new_line();//display a new prompt at the right position
	rl_redisplay();//redisplay the prompt
*/
void	signal_handler_int(int signum)
{
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = SIGINT;
	}
}

//write out the new line to STDERR
void	signal_handler_int_child(int signum)
{
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		g_signal = SIGINT;
	}
}

void	signal_handler_quit_child(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_printf_fd(STDERR_FILENO, "Quit: %d\n", g_signal);
		g_signal = SIGQUIT;
	}
}

void	signal_handler_int_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		rl_done = 1;
		g_signal = SIGINT;
	}
}

void	*rl_quit(void)
{
	if (g_signal == SIGINT)
	{
		rl_done = 1;
		g_signal = SIGINT;
	}
	return (NULL);
}

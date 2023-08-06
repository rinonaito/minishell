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

extern int	g_signal;// = 0;//no initializer

void	signal_handler_int(int signum)
{
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);//write out the new line to STDERR
		rl_replace_line("", 0);//replace the line with empty string
		rl_on_new_line();//display a new prompt at the right position
		rl_redisplay();//redisplay the prompt
		g_signal = 1;
	}
}

void	signal_handler_int_child(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 2;
		write(STDERR_FILENO, "\n", 1);//write out the new line to STDERR
	}
}

void	signal_handler_quit_child(int signum)
{
	if (signum == SIGQUIT)
	{
		g_signal = 3;
		ft_printf_fd(STDERR_FILENO, "Quit: %d\n", g_signal);
	}
}

void	signal_handler_int_heredoc(int signum)
{
	//printf(">%s\n", __func__);
	if (signum == SIGINT)
	{
		g_signal = 1;
		rl_done = 1;
		//close(STDIN_FILENO);
		//ft_printf_fd(STDERR_FILENO, "Quit: %d\n", g_signal);
	}
}

//void	test_handler(int signum)
//{
	//printf(">%s\n", __func__);
//}

void	ft_signal(int *status)
{
	/*** SIGQUIT ***/
	signal(SIGQUIT, SIG_IGN);
	//sigemptyset(&sig_info->sa_quit.sa_mask);
	//sig_info->sa_quit.sa_flags = 0;
	//sig_info->sa_quit.sa_handler = SIG_IGN;//signal_handler_quit;
	//if (sigaction(SIGQUIT, &sig_info->sa_quit, NULL) < 0)
		//ft_perror("sigaction");

	/*** SIGINT ***/
	signal(SIGINT, signal_handler_int);
	//sigemptyset(&sig_info->sa_int.sa_mask);//clear signal masks
	//sig_info->sa_int.sa_flags = 0;//set no flag
	//sig_info->sa_int.sa_handler = signal_handler_int;
	//if (sigaction(SIGINT, &sig_info->sa_int, NULL) < 0)
		//ft_perror("sigaction");
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

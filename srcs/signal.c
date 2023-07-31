/* ************************************************************************** */
/*                                                                            */
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
		//printf("g_signal:[%d]\n", g_signal);
		g_signal = 1;
		//printf("g_signal:[%d]\n", g_signal);
	}
}

void	signal_handler_quit(int signum)
{
}

void	test_handler(int signum)
{
	printf(">%s\n", __func__);
}

void	ft_signal(void)
{
	//initialize the sigaction
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	/*** SIGQUIT ***/
	//signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;//signal_handler_quit;
	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
		ft_perror("sigaction");

	/*** SIGINT ***/
	sigemptyset(&sa_int.sa_mask);//clear signal masks
	sa_int.sa_flags = 0;//set no flag
	sa_int.sa_handler = signal_handler_int;
	if (sigaction(SIGINT, &sa_quit, NULL) < 0)
		ft_perror("sigaction");
}

void	ft_signal_child(void)
{
	//initialize the sigaction
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	/*** SIGQUIT ***/
	//signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
		ft_perror("sigaction");

	/*** SIGINT ***/
	sigemptyset(&sa_int.sa_mask);//clear signal masks
	sa_int.sa_flags = 0;//set no flag
	sa_int.sa_handler = signal_handler_int;
	if (sigaction(SIGINT, &sa_quit, NULL) < 0)
		ft_perror("sigaction");
}

/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:59:38 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/25 20:15:35 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

extern int	g_signal;// = 0;//no initializer

void	signal_handler_int(int signum)
{
	signal(SIGINT, SIG_IGN);
	//printf(">%s\n", __func__);
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

void	signal_handler_int_child(int signum)
{
	printf("\n***>%s***\n", __func__);
	write(STDERR_FILENO, "SIGINT_CHILD\n", 13);
	if (signum == SIGINT)
	{
		g_signal = 2;
		/*
		write(STDERR_FILENO, "\n", 1);//write out the new line to STDERR
		rl_replace_line("", 0);//replace the line with empty string
		rl_on_new_line();//display a new prompt at the right position
		rl_redisplay();//redisplay the prompt
		//printf("g_signal:[%d]\n", g_signal);
		g_signal = 2;
		//printf("g_signal:[%d]\n", g_signal);
		*/
	}
}

void	signal_handler_quit(int signum)
{
}

void	signal_handler_quit_child(int signum)
{
	printf("\n***>%s***\n", __func__);
	write(STDERR_FILENO, "SIGQUIT_CHILD\n", 14);
	if (signum == SIGQUIT)
	{
		g_signal = 3;
	}
}

void	test_handler(int signum)
{
	printf(">%s\n", __func__);
}

void	ft_signal(t_signal *sig_info)
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
}

void	ft_signal_child(t_signal *sig_info)
{
	/*** SIGQUIT ***/
	signal(SIGQUIT, signal_handler_quit_child);
	//sigemptyset(&sig_info->sa_quit.sa_mask);
	//sig_info->sa_quit.sa_flags = 0;
		//sig_info->sa_quit.sa_handler = signal_handler_quit_child;
	//sig_info->sa_quit.sa_handler = test_handler;
	//if (sigaction(SIGQUIT, &sig_info->sa_quit, NULL) < 0)
		//ft_perror("sigaction");

	/*** SIGINT ***/
	signal(SIGINT, signal_handler_int_child);
	//sigemptyset(&sig_info->sa_int.sa_mask);//clear signal masks
	//sig_info->sa_int.sa_flags = 0;//set no flag
		//sig_info->sa_int.sa_handler = signal_handler_int_child;
	//sig_info->sa_int.sa_handler = test_handler;
	//if (sigaction(SIGINT, &sig_info->sa_int, NULL) < 0)
		//ft_perror("sigaction");
}

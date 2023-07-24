/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:59:38 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/24 19:42:46 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	signal_handler_int(int signum)
{
	if (signum == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();//display a new prompt
		rl_redisplay();
	}
}

void	signal_handler_quit(int signum)
{
}

void	test_handler(int signum)
{
	printf(">%s\n", __func__);
}

void	ft_signal(int input)
{
	//initialize the sigaction
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	int					ret;

	/*** SIGQUIT ***/
	signal(SIGQUIT, SIG_IGN);
	//sigemptyset(&sa_quit.sa_mask);
	//sa_quit.sa_flags = 0;
	//sa_quit.sa_handler = signal_handler_quit;
	//if (sigaction(SIGINT, &sa_quit, NULL) < 0)
		//ft_perror("sigaction");

	/*** SIGINT ***/
	sigemptyset(&sa_int.sa_mask);//clear signal masks
	sa_int.sa_flags = 0;//set no flag
	if (input == 0)
		sa_int.sa_handler = signal_handler_int;
	ret = sigaction(SIGINT, &sa_int, NULL);
	if (ret < 0)
		ft_perror("sigaction");

}

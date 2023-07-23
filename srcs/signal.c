/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taaraki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:59:38 by taaraki           #+#    #+#             */
/*   Updated: 2023/07/23 21:31:12 by taaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	signal_handler_int(int signum)
{
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
	struct sigaction	act;
	int					ret;

	sigemptyset(&act.sa_mask);
	if (input == 0)
		act.sa_handler = test_handler;
	else if (input == 1)
		act.sa_handler = signal_handler_int;
	ret = sigaction(SIGINT, &act, NULL);
	if (ret < 0)
		ft_perror("sigaction");
	//sigemptyset(&act.sa_mask);
	if (input == 0)
		act.sa_handler = test_handler;
	else if (input == 1)
		act.sa_handler = signal_handler_quit;
	ret = sigaction(SIGQUIT, &act, NULL);
	if (ret < 0)
		ft_perror("sigaction");
}
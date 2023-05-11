/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 02:43:50 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/05/11 00:07:51 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_voider(int signal)
{
	(void)signal;
	write(1, "\033[A", 3);
	ioctl(0, TIOCSTI, "\n");
}

void	eof_control(char *line)
{
	if (!line)
	{
		write(1, "\033[2D", 4);
		printf("exit\n");
		exit (0);
	}
}

void	sigquit_voider(int signal)
{
	(void)signal;

	// ioctl(0, TIOCSTI, " ");
	// write(1, "\033[D", 3);
	// ioctl(0, TIOCSTI, NULL);
	if (g_arg.quit_flag == 1)
	{
		//printf("in");
		write(1, "\033[2D", 4);
		write(1, "  ", 2);
		write(1, "\033[2D", 4);
		g_arg.quit_flag = 0;
	}
	//printf("sigquit\n");
	g_arg.quit_flag = 1;
}

void	signal_handler(int signal)
{
	g_arg.sigusr_i++;
	if (signal == SIGUSR1)
		g_arg.cmds[g_arg.sigusr_i - 1]->tmp_hdcount = 0;
}

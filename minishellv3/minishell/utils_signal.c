/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 02:43:50 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/05/29 22:00:57 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_voider(int signal)
{
	//write(1, "\033[2D", 2); //yukari
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
	//write(1, "\033[32mminishell$   ", 18);
}

void	eof_control(char *line)
{
	if (!line)
	{
		write(1, "\033[A", 3);
		write(1, "\033[32mminishell$ ", 16);
		write(1, "\033[0mexit\n", 9);
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

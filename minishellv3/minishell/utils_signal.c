/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 02:43:50 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/05/31 14:41:32 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_voider(int signal)
{
	int	i;
	int	j;

	//write(1, "\033[2D", 2); //yukari
	if (g_arg.pipe_count == -1)
	{
		//write(1, "\n", 1);
		write(1, "\033[A", 3);
		ioctl(0, TIOCSTI, "\n");
		/*rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();*/
	}
	else if (g_arg.pipe_count > -1)
	{
		i = -1;
		while (++i < g_arg.pipe_count + 1)
		{
			j = -1;
			while (++j < g_arg.cmds[i]->tmp_hdcount)
				if (g_arg.cmds[i]->heredoc[j].pid == 0)
					kill(g_arg.cmds[i]->heredoc[j].pid, SIGUSR2);
			if (g_arg.pid[i] == 0)
				kill(g_arg.pid[i], SIGUSR2);
		}
		write(1, "\n", 1);
		//rl_on_new_line();
		//write(1, "\033[2D", 4);
	}
	(void)signal;
	//kill(0, SIGUSR2);
	//write(1, "\033[32mminishell$   ", 18);
}

void	eof_control(char *line)
{
	if (!line)
	{
		//write(1, "\033[A", 3);
		//write(1, "\033[32mminishell$ ", 16);
		write(1, "\033[2D", 4);
		write(1, "\033[0mexit\n", 9);
		exit(0);
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

void	child_signal_handler(int signal)
{
	if (signal == SIGUSR2)
		exit(0);
}

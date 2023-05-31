/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:29 by melih             #+#    #+#             */
/*   Updated: 2023/05/31 19:16:52 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(void)
{
	signal(SIGINT, &sigint_voider);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, &signal_handler);
	signal(SIGUSR2, &signal_handler);
}

void	set_start(char **envp)
{
	g_arg.pipe_count = -1;
	handle_signal();
	get_env(envp);
	g_arg.list = NULL;
	set_export();
	g_arg.pipe_count = -1;
}

int	routine(void)
{
	count_arg();
	flag_setter();
	find_path(g_arg.env);
	g_arg.cmd_paths = ft_split(g_arg.paths, ':');
	find_pwd(g_arg.env);
	if (spreader())
	{
		refresh_counts();
		return (1);
	}
	g_arg.quit_flag = 0;
	refresh_counts();
	free(g_arg.input);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	set_start(envp);
	while (1)
	{
		g_arg.input_ctl = 0;
		g_arg.input = readline("minishell$ ");
		eof_control(g_arg.input);
		if (*g_arg.input != '\n' && *g_arg.input != '\0')
		{
			add_history(g_arg.input);
			list_init(g_arg.input);
			if (check_quote(g_arg.input) || pipe_check()
				|| g_arg.input_ctl == 1)
			{
				free(g_arg.input);
				continue ;
			}
			if (routine())
				continue ;
		}
		else if (*g_arg.input == 0)
			free(g_arg.input);
	}
	return (0);
}

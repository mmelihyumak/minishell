/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:29 by melih             #+#    #+#             */
/*   Updated: 2023/05/27 20:42:57 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(void)
{
	signal(SIGINT, &sigint_voider);
	signal(SIGQUIT, &sigquit_voider);
	signal(SIGUSR1, &signal_handler);
}

void	set_start(char **envp)
{
	handle_signal();
	get_env(envp);
	g_arg.list = NULL;
	set_export();
}

void	routine(void)
{
	count_arg();
	flag_setter();
	find_path(g_arg.env);
	g_arg.cmd_paths = ft_split(g_arg.paths, ':');
	find_pwd(g_arg.env);
	spreader();
	g_arg.quit_flag = 0;
	refresh_counts();
	free(g_arg.input);
}

int	main(int argc, char **argv, char **envp)
{
	set_start(envp);
	while (1)
	{
		g_arg.input = readline("minishell$ ");
		eof_control(g_arg.input);
		if (*g_arg.input != '\n' && *g_arg.input != '\0')
		{
			add_history(g_arg.input);
			list_init(g_arg.input);
			if (check_quote(g_arg.input) || pipe_check())
			{
				free(g_arg.input);
				continue ;
			}
			routine();
		}
		else if (*g_arg.input == 0)
			free(g_arg.input);
	}
	return (0);
}

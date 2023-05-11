/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:29 by melih             #+#    #+#             */
/*   Updated: 2023/05/11 05:19:41 by muyumak          ###   ########.fr       */
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
	g_arg.paths = find_path(g_arg.env);
	g_arg.cmd_paths = ft_split(g_arg.paths, ':');
	g_arg.pwd = find_pwd(g_arg.env);
	set_export();
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
			last_of_list();
			count_arg();
			flag_setter();
			if (!pipe_check())
				spreader();
			else
				continue ;
			g_arg.quit_flag = 0;
			refresh_counts();
			free(g_arg.input);
		}
		else if (*g_arg.input == 0)
			free(g_arg.input);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:29 by melih             #+#    #+#             */
/*   Updated: 2023/03/23 03:46:37 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	signal(SIGINT, &sigint_voider);
	signal(SIGQUIT, &sigquit_voider);
	g_arg.paths = find_path(envp);
	g_arg.cmd_paths = ft_split(g_arg.paths, ':');
	while (1)
	{
		input = readline("minishell> ");
		eof_control(input);
		if (*input != '\n' && *input != '\0')
			add_history(input);
		g_arg.args = ft_split(input, ' ');
		cmd_process(envp, input);
		g_arg.quit_flag = 0;
	}
	return (0);
}

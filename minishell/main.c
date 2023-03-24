/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:29 by melih             #+#    #+#             */
/*   Updated: 2023/03/24 04:02:54 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_first_arg(void)
{
	if (!ft_strncmp("exit", g_arg.args[0], 4))
	{
		printf("exit\n");
		exit(0);
	}
	else if (!ft_strncmp("<", g_arg.args[0], 1))
	{
		if (!g_arg.args[1])
			printf("minishell: syntax error near unexpected token `newline'\n");
		else
			open_folder();
	}
	else
	{
		cmd_process(g_arg.envp);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	signal(SIGINT, &sigint_voider);
	signal(SIGQUIT, &sigquit_voider);
	g_arg.paths = find_path(envp);
	g_arg.cmd_paths = ft_split(g_arg.paths, ':');
	while (1)
	{
		input = readline("minishell$ ");
		eof_control(input);
		if (*input != '\n' && *input != '\0')
			add_history(input);
		g_arg.args = ft_split(input, ' ');
		g_arg.envp = envp;
		get_first_arg();
		g_arg.quit_flag = 0;
	}
	return (0);
}

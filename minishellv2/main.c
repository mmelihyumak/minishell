/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:29 by melih             #+#    #+#             */
/*   Updated: 2023/04/01 12:19:39 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	get_envp(char **envp)
{
	int	i;
	int	envp_len;

	i = -1;
	envp_len = split_len(envp);
	g_arg.envp = malloc(sizeof(char *) * (envp_len + 1));
	while (envp[++i])
		g_arg.envp[i] = ft_strdup(envp[i]);
	g_arg.envp[i] = 0;
}

void	free_split(char **splitted)
{
	int	i;

	i = -1;
	if (splitted)
	{
		while (splitted[++i])
			free(splitted[i]);
		free(splitted);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	signal(SIGINT, &sigint_voider);
	signal(SIGQUIT, &sigquit_voider);
	g_arg.list = NULL;
	get_envp(envp);
	g_arg.paths = find_path(g_arg.envp);
	g_arg.cmd_paths = ft_split(g_arg.paths, ':');
	while (1)
	{
		input = readline("minishell$ ");
		eof_control(input);
		if (*input != '\n' && *input != '\0')
		{
			add_history(input);
			list_init(input);
			arg_count();
			//print_input();
			spreader();
			g_arg.quit_flag = 0;
			if (g_arg.fd_in > 2)
				close(g_arg.fd_in);
			if (g_arg.fd_out > 2)
				close(g_arg.fd_out);
			//free_split();
		}
		else if (*input == 0)
		{
			//system("leaks minishell");
		}
		free(input);
		if (g_arg.will_free)
			free_split(g_arg.cmd_args);
		g_arg.will_free = 0;
		system("leaks minishell");
	}
	return (0);
}

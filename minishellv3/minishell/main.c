/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:29 by melih             #+#    #+#             */
/*   Updated: 2023/05/05 11:35:49 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_input(char **strings)
{
	int	i;

	i = -1;
	while (strings[++i])
		printf("string[%d]: %s\n", i, strings[i]);
}

int	get_first_arg(void)
{
	return (0);
}

void	free_split(char **strings)
{
	int	i;

	i = -1;
	while (strings[++i])
	{
		//printf("strings[%d]: %p\n", i, strings[i]);
		free(strings[i]);		
	}
	free(strings);
}

int	main(int argc, char **argv, char **envp)
{
	signal(SIGINT, &sigint_voider);
	signal(SIGQUIT, &sigquit_voider);
	get_env(envp);
	g_arg.list = NULL;
	g_arg.paths = find_path(g_arg.env);
	g_arg.cmd_paths = ft_split(g_arg.paths, ':');
	g_arg.pwd = find_pwd(g_arg.env);
	set_export();
	while (1)
	{
		g_arg.input = readline("minishell$ ");
		eof_control(g_arg.input);
		if (*g_arg.input != '\n' && *g_arg.input != '\0')
		{
			add_history(g_arg.input);
			//g_arg.args = ft_split_quotes(input);
			list_init(g_arg.input);
			count_arg();
			flag_setter();
			t_arg_list	*temp;
			temp = g_arg.list;
			while (temp)
			{
				printf("flag: %c\n", temp->flag);
				temp = temp->next;
			}
			//printf("arg_count: %d\n", g_arg.arg_count);
			//printf("pipe_count: %d\n", g_arg.pipe_count);
			if (!pipe_check())
			{
				spreader();
			}
			else
				continue ;
			//print_input();
			//get_first_arg();
			//cmd_process(envp);
			g_arg.quit_flag = 0;
			refresh_counts();
			free(g_arg.input);
			//free_split();
		}
		else if (*g_arg.input == 0)
		{
			free(g_arg.input);
			//system("leaks minishell");
		}
		//system("leaks minishell");
	}
	return (0);
}

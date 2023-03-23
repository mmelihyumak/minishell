/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 02:25:38 by melih             #+#    #+#             */
/*   Updated: 2023/03/23 02:30:10 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
	}
	return (*envp + 5);
}

int	cmd_process(char **envp, char *input)
{
	char	*x;

	g_arg.pid = fork();
	if (g_arg.pid == 0)
	{
		g_arg.cmd_args = &g_arg.args[0];
		g_arg.cmd = get_cmd(g_arg.cmd_paths, g_arg.cmd_args[0]);
		if (!g_arg.cmd)
		{
			exit(1);
		}
		execve(g_arg.cmd, g_arg.cmd_args, envp);
	}
	waitpid(g_arg.pid, NULL, 0);
	return (0);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*command;
	char	*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (0);
}

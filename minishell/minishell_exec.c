/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 02:25:38 by melih             #+#    #+#             */
/*   Updated: 2023/03/26 04:04:45 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			return (envp[i] + 5);
	}
	return (0);
}

char	*find_pwd(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PWD", envp[i], 3))
			return (envp[i] + 4);
	}
	return (0);
}

int	cmd_process(char **envp)
{
	char	*x;

	g_arg.pid = fork();
	if (g_arg.pid == 0)
	{
		g_arg.cmd_args = &g_arg.args[0];
		if (g_arg.args[0][0] == '/')
			execve(g_arg.args[0], g_arg.cmd_args, envp);
		g_arg.cmd = get_cmd(g_arg.cmd_paths, g_arg.cmd_args[0]);
		if (!g_arg.cmd)
		{
			printf("minishell: %s: command not found\n", g_arg.cmd_args[0]);
			exit(0);
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

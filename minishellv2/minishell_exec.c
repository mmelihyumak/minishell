/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 02:25:38 by melih             #+#    #+#             */
/*   Updated: 2023/04/01 07:12:07 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **envp)
{
	int	i;

	i = -1;
	while (g_arg.envp[++i])
	{
		if (!ft_strncmp("PATH", g_arg.envp[i], 4))
			return (g_arg.envp[i] + 5);
	}
	return (0);
}

char	*find_pwd(char **envp)
{
	int	i;

	i = -1;
	while (g_arg.envp[++i])
	{
		if (!ft_strncmp("PWD", g_arg.envp[i], 3))
			return (g_arg.envp[i] + 4);
	}
	return (0);
}

int	cmd_process(char **envp, int fd_in, int fd_out)
{
	char	*x;

	g_arg.pid = fork();
	if (g_arg.pid == 0)
	{
		if (fd_in != 0)
			dup2(fd_in, 0);
		if (fd_out != 0)
			dup2(fd_out, 1);
		if (g_arg.cmd_args[0][0] == '/')
			execve(g_arg.cmd_args[0], g_arg.cmd_args, envp);
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

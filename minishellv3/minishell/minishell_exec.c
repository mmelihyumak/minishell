/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 02:25:38 by melih             #+#    #+#             */
/*   Updated: 2023/05/08 04:23:47 by melih            ###   ########.fr       */
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

void	here_doc_process(t_cmd *command, int hd_id)
{
	command->heredoc[hd_id].pid = fork();
	if (command->heredoc[hd_id].pid == 0)
	{
		while (1)
		{
			command->heredoc[hd_id].input = readline("> ");
			if (ft_strcmp(command->heredoc[hd_id].input, command->heredoc[hd_id].here_doc_name) == 0)
				exit(0);
		}
	}
}

void	open_heredoc(t_cmd *command)
{
	int	i;

	i = -1;
	while (++i < command->heredoc_count)
	{
		here_doc_process(command, i);
		wait(&command->heredoc[i].pid);
	}
	kill(g_arg.pid[1], SIGUSR1);
	//printf("command->tmp_hdcount: %d\n", command->tmp_hdcount);
}

void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		g_arg.cmds[0]->tmp_hdcount = 0;
}

int	cmd_process(char **envp, int i, int j)
{
	signal(SIGUSR1, &signal_handler);
	g_arg.pid[i] = fork();
	if (g_arg.pid[i] == 0)
	{
		if (i == 1)
		{
			while (1)
			{
				if (g_arg.cmds[i - 1]->tmp_hdcount == 0)
					break ;
			}
		}
		if (g_arg.cmds[i]->heredoc_count != 0)
			open_heredoc(g_arg.cmds[i]);
		close_fd(g_arg.cmds[i]);
		dup2(g_arg.cmds[i]->fd_in, STDIN_FILENO);
		dup2(g_arg.cmds[i]->fd_out, STDOUT_FILENO);
		if (!executor(i))
			exit(0);
		g_arg.cmd = get_cmd(g_arg.cmd_paths, g_arg.cmds[i]->cmd_args[0]);
		if (!g_arg.cmd)
		{
			printf("minishell: %s: command not found\n", g_arg.cmds[i]->cmd_args[0]);
			exit(127);
		}
		execve(g_arg.cmd, g_arg.cmds[i]->cmd_args, g_arg.env);
	}
	return (0);
}

void	print_closing_fd(int fd)
{
	printf("closing_fd: %d\n", fd);
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

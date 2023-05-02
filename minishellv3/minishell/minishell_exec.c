/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 02:25:38 by melih             #+#    #+#             */
/*   Updated: 2023/05/03 01:45:37 by melih            ###   ########.fr       */
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

int	here_doc_process(t_cmd *command)
{
	char	*temp;
	g_arg.heredoc_pid = fork();
	if (g_arg.heredoc_pid == 0)
	{
		close(command->here_doc.tubes[0]);
		while (1)
		{
			g_arg.here_doc_input = readline("> ");
			if (!ft_strncmp(command->here_doc_name, g_arg.here_doc_input, ft_strlen(g_arg.here_doc_input)))
				exit(0);
			temp = ft_strjoin(g_arg.here_doc_input, "\n");
			write(command->here_doc.tubes[1], temp, ft_strlen(temp));
			free(temp);
		}
		exit(0);
	}
	return (0);
}

int	cmd_process(char **envp, int i, int j)
{
	g_arg.pid[i] = fork();
	if (g_arg.pid[i] == 0)
	{
		if (g_arg.cmds[i]->here_doc.here_doc_name)
		{
			here_doc_process(g_arg.cmds[i]);
			waitpid(g_arg.heredoc_pid, NULL, 0);
		}
		else
		{
			close(g_arg.cmds[0]->here_doc.tubes[0]);
			close(g_arg.cmds[0]->here_doc.tubes[1]);
		}
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

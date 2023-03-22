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

int	cmd_process(t_arg *arg, char **envp, char *input)
{
	char	*x;

	arg->pid = fork();
	if (arg->pid == 0)
	{
		arg->cmd_args = &arg->args[0];
		arg->cmd = get_cmd(arg->cmd_paths, arg->cmd_args[0]);
		if (!arg->cmd)
		{
			exit(1);
		}
		execve(arg->cmd, arg->cmd_args, envp);
	}
	waitpid(arg->pid, NULL, 0);
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

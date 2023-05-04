/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spreader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:40:29 by melih             #+#    #+#             */
/*   Updated: 2023/05/03 17:05:34 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(int i)
{
	if (!ft_strncmp("env", g_arg.cmds[i]->cmd_args[0], ft_strlen(g_arg.cmds[i]->cmd_args[0])))
	{
		print_input(g_arg.env);
		return (0);
	}
	else if (!ft_strncmp("pwd", g_arg.cmds[i]->cmd_args[0], ft_strlen(g_arg.cmds[i]->cmd_args[0])))
	{
		//exec_pwd();
		printf("%s\n", g_arg.pwd);
		return (0);
	}
	else if (!ft_strncmp("echo", g_arg.cmds[i]->cmd_args[0], ft_strlen(g_arg.cmds[i]->cmd_args[0])))
	{
		exec_echo(i);
		return (0);
	}
	else if (!ft_strncmp("export", g_arg.cmds[i]->cmd_args[0], ft_strlen(g_arg.cmds[i]->cmd_args[0])))
	{
		exec_export(i);
		return (0);
	}
	else if (!ft_strncmp("cd", g_arg.cmds[i]->cmd_args[0], ft_strlen(g_arg.cmds[i]->cmd_args[0])))
	{
		exec_cd(i);
		return (0);
	}
	return (1);
}

void	spreader(void)
{
	t_arg_list	*temp;
	int	i;
	int	j;

	temp = g_arg.list;
	i = 0;
	j = 0;
	printf("pid_address: %p\n", g_arg.pid);
	g_arg.pid = malloc(sizeof(pid_t) * (g_arg.pipe_count + 1));
	if (g_arg.pipe_count > 0)
		open_pipes();
	g_arg.commands = malloc(sizeof(char **) * (g_arg.pipe_count + 1));
	while (temp)
	{
		i = 0;
		g_arg.commands[j] = malloc(sizeof(char *) * (count_cmd_arg(temp) + 1));
		while (temp)
		{
			if (temp->flag == 'o')
			{
				g_arg.commands[j][i] = ft_strdup(temp->content);
				i++;
			}
			if (temp->flag == '|')
				break ;
			temp = temp->next;
		}
		g_arg.commands[j][i] = 0;
		print_input(g_arg.commands[j]);
		if (temp)
		{
			if (temp->flag == '|')
			{
				if (temp->next)
					temp = temp->next;
				else
					break ;	
			}
		}
		else
			break ;
		j++;
	}
	t_cmd_settings();
	set_tubes();
	set_fds();
	print_t_cmd();
	//printf("fd_in: %d\n", g_arg.cmds[1]->fd_in);
	//printf("fd_out: %d\n", g_arg.cmds[1]->fd_out);
	i = -1;
	j = 0;
	while (++i < g_arg.pipe_count + 1)
	{
		if (!ft_strncmp("cd", g_arg.cmds[i]->cmd_args[0], ft_strlen(g_arg.cmds[i]->cmd_args[0])))
			exec_cd(i);
		else
			cmd_process(g_arg.env, i, j);
		if (i % 2 == 0 && i != 0)
			j++;
	}
	close_tubes();
	wait_process();
}

void	print_t_cmd(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_arg.pipe_count + 1)
	{
		printf("\n");
		printf("cmds[%d] infile: %s fd: %d\n", i, g_arg.cmds[i]->infile_name, g_arg.cmds[i]->fd_in);
		printf("cmds[%d] outfile: %s fd: %d\n", i, g_arg.cmds[i]->outfile_name, g_arg.cmds[i]->fd_out);
		if (g_arg.cmds[i]->here_doc_name)
			printf("here_doc: %s\n", g_arg.cmds[i]->here_doc_name);
		j = 0;
		while (g_arg.cmds[i]->cmd_args[j])
		{
			printf("cmds[%d] args[%d]: address: %p-> value: %s\n"
				, i, j, g_arg.cmds[i]->cmd_args, g_arg.cmds[i]->cmd_args[j]);
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spreader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:40:29 by melih             #+#    #+#             */
/*   Updated: 2023/05/31 21:08:01 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(int i)
{
	if (!ft_strcmp("env", g_arg.cmds[i]->cmd_args[0]))
	{
		print_input(g_arg.env);
		return (0);
	}
	else if (!ft_strcmp("pwd", g_arg.cmds[i]->cmd_args[0]))
	{
		printf("%s\n", g_arg.pwd);
		return (0);
	}
	else if (!ft_strcmp("echo", g_arg.cmds[i]->cmd_args[0]))
	{
		exec_echo(i);
		return (0);
	}
	else if (!ft_strcmp("export", g_arg.cmds[i]->cmd_args[0]))
	{
		if (split_len(g_arg.cmds[i]->cmd_args) == 1)
			ft_smart_putstr(g_arg.exports);
		return (0);
	}
	return (1);
}

int	executor_v2(int i)
{
	if (!ft_strcmp("export", g_arg.cmds[i]->cmd_args[0]))
	{
		if (split_len(g_arg.cmds[i]->cmd_args) > 1)
			exec_export(i);
		else
			return (1);
		return (0);
	}
	else if (!ft_strcmp("cd", g_arg.cmds[i]->cmd_args[0]))
	{
		exec_cd(i);
		return (0);
	}
	else if (!ft_strcmp("unset", g_arg.cmds[i]->cmd_args[0]))
	{
		if (split_len(g_arg.cmds[0]->cmd_args) > 1)
			exec_unset();
		else
			return (2);
		return (0);
	}
	return (1);
}

int	spreader_v2(t_arg_list **list, int j)
{
	int	i;

	i = 0;
	while (*list)
	{
		if ((*list)->flag == 'o')
			g_arg.commands[j][i++] = ft_strdup((*list)->content);
		if ((*list)->flag == '|')
			break ;
		(*list) = (*list)->next;
	}
	g_arg.commands[j][i] = 0;
	if ((*list))
	{
		if ((*list)->flag == '|')
		{
			if ((*list)->next)
				(*list) = (*list)->next;
			else
				return(1);
		}
	}
	else
		return(1);
	return (0);
}

int	spreader_v3(void)
{
	int	i;
	
	t_cmd_settings();
	set_tubes();
	if (set_fds())
		return (1);
	set_heredocs();
	i = -1;
	while (++i < g_arg.pipe_count + 1)
		if (executor_v2(i) == 1)
			cmd_process(g_arg.env, i);
	close_heredoc_tubes();
	close_tubes();
	wait_process();
	return (0);
}

int	spreader(void)
{
	t_arg_list	*temp;
	int	j;
	int	i;

	temp = g_arg.list;
	g_arg.pid = malloc(sizeof(pid_t) * (g_arg.pipe_count + 1));
	if (g_arg.pipe_count > 0)
		open_pipes();
	g_arg.commands = malloc(sizeof(char **) * (g_arg.pipe_count + 2));
	j = -1;
	while (temp)
	{
		i = 0;
		g_arg.commands[++j] = malloc(sizeof(char *) * (count_cmd_arg(temp) + 1));
		if (spreader_v2(&temp, j))
			break ;
	}
	g_arg.commands[j + 1] = NULL;
	if (spreader_v3())
		return (1);
	return (0);
}

// ALTTAKİ FONKSİYON SİLİNECEK

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
		printf("cmds[%d] heredoc_count: %d\n", i, g_arg.cmds[i]->heredoc_count);
		printf("cmds[%d] temp_heredoc_count: %d\n", i, g_arg.cmds[i]->tmp_hdcount);
		j = -1;
		while (++j < g_arg.cmds[i]->heredoc_count)
			printf("cmds[%d].heredoc[%d].heredoc_name = %s\n", i, j, g_arg.cmds[i]->heredoc[j].here_doc_name);
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

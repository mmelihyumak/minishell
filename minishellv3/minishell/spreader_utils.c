/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spreader_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:25:52 by melih             #+#    #+#             */
/*   Updated: 2023/05/31 14:55:10 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_arg(void)
{
	t_arg_list	*temp;

	temp = g_arg.list;
	while (temp)
	{
		if (temp->flag == '|')
			g_arg.pipe_count++;
		g_arg.arg_count++;
		temp = temp->next;
	}
	g_arg.pipe_count++;
}

int	flag_setter(void)
{
	t_arg_list	*temp;
	int			i;

	temp = g_arg.list;
	i = 0;
	while (temp)
	{
		if (temp->flag == '>')
			if (temp->next)
				temp->next->flag = 't';
		if (temp->flag == '<')
			if (temp->next)
				temp->next->flag = 'i';
		if (ft_strcmp(temp->content, "<<") == 0)
		{
			temp->flag = 'h';
			if (temp->next)
				temp->next->flag = 'e';
		}
		if (ft_strcmp(temp->content, ">>") == 0)
		{
			temp->flag = 'a';
			if (temp->next)
				temp->next->flag = 'p';
		}
		temp = temp->next;
	}
	return (0);
}

int	count_cmd_arg(t_arg_list *temp)
{
	int	i;

	i = 0;
	while (temp)
	{
		if (temp->flag == 'o')
			i++;
		if (temp->flag == '|')
			break ;
		temp = temp->next;
	}
	return (i);
}

void	refresh_counts(void)
{
	if (!pipe_check())
	{
		free_commands();
		g_arg.arg_count = 0;
		g_arg.pipe_count = -1;
		g_arg.sigusr_i = 0;
		if (g_arg.pwd != NULL)
			free(g_arg.pwd);
		if (g_arg.paths != NULL)
			free(g_arg.paths);
		if (g_arg.cmd_paths != NULL)
			free_split(g_arg.cmd_paths);
	}
}

void	free_commands(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		j = -1;
		free_split(g_arg.commands[i]);
		while (++j < g_arg.cmds[i]->heredoc_count)
			free(g_arg.cmds[i]->heredoc[j].here_doc_name);
		free(g_arg.cmds[i]->heredoc);
		free(g_arg.cmds[i]);
	}
	free(g_arg.cmds);
	free(g_arg.commands);
	free(g_arg.pid);
	g_arg.pid = NULL;
	i = -1;
	while (++i < g_arg.pipe_count)
		free(g_arg.tubes[i]);
	if (g_arg.pipe_count > 0)
		free(g_arg.tubes);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spreader_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:25:52 by melih             #+#    #+#             */
/*   Updated: 2023/05/04 22:11:09 by melih            ###   ########.fr       */
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
		if (temp->flag == 'h')
			g_arg.heredoc_count++;
		g_arg.arg_count++;
		temp = temp->next;
	}
}

int	flag_setter(void)
{
	t_arg_list	*temp;
	int	i;

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
		if (!ft_strncmp("<<", temp->content, 2))
		{
			temp->flag = 'h';
			if (temp->next)
				temp->next->flag = 'e';
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
	printf("count_cmd_arg: %d\n", i);
	return (i);
}

void	refresh_counts(void)
{
	if (!pipe_check())
	{
		free_commands();
		g_arg.arg_count = 0;
		g_arg.pipe_count = 0;
	}
}

void	free_commands(void)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		free_split(g_arg.commands[i]);
		free(g_arg.cmds[i]);
	}
	free(g_arg.cmds);
	free(g_arg.commands);
	free(g_arg.pid);
	i = -1;
	while (++i < g_arg.pipe_count)
		free(g_arg.tubes[i]);
	if (g_arg.pipe_count > 0)
		free(g_arg.tubes);
}

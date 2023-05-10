/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 02:04:40 by melih             #+#    #+#             */
/*   Updated: 2023/05/10 20:23:33 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	i = -1;
	while (s1[++i])
	{
		if (s1[i] != s2[i])
			return (-1);
	}	
	return (0);
}

void	count_heredoc(t_cmd *command)
{
	static t_arg_list	*temp;
	int	i;

	i = 0;
	if (temp == NULL)
		temp = g_arg.list;
	while (temp && temp->flag != '|')
	{
		if (temp->flag == 'h')
			command->heredoc_count++;
		temp = temp->next;
	}
	if (temp && temp->flag == '|' && temp->next != NULL)
		temp = temp->next;
	command->tmp_hdcount = command->heredoc_count;
}

void	set_heredoc_name(t_cmd *command)
{
	t_arg_list	*temp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	temp = g_arg.list;
	while (temp)
	{
		if (temp->flag == 'e')
		{
			g_arg.cmds[i]->heredoc[j].here_doc_name = ft_strdup(temp->content);
			j++;
		}
		if (temp->flag == '|')
		{
			i++;
			j = 0;
		}
		temp = temp->next;
	}
}

void	set_heredoc_tubes(t_cmd *command)
{
	pipe(command->heredoc[command->heredoc_count - 1].tubes);
	command->fd_in = command->heredoc[command->heredoc_count - 1].tubes[0];
}

void	close_heredoc_tubes(void)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		if (g_arg.cmds[i]->heredoc_count > 0)
		{
			close(g_arg.cmds[i]->heredoc[g_arg.cmds[i]->heredoc_count - 1].tubes[0]);
			close(g_arg.cmds[i]->heredoc[g_arg.cmds[i]->heredoc_count - 1].tubes[1]);
		}
	}
}

void	close_other_heredocs(t_cmd *command)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		if (g_arg.cmds[i]->heredoc != command->heredoc)
		{
			close(g_arg.cmds[i]->heredoc[g_arg.cmds[i]->heredoc_count - 1].tubes[1]);
			close(g_arg.cmds[i]->heredoc[g_arg.cmds[i]->heredoc_count - 1].tubes[0]);
		}
	}
}

void	set_heredocs(void)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		count_heredoc(g_arg.cmds[i]);
		if (g_arg.cmds[i]->heredoc_count > 0)
		{
			g_arg.cmds[i]->heredoc = malloc(sizeof(t_heredoc) * g_arg.cmds[i]->heredoc_count);
			set_heredoc_tubes(g_arg.cmds[i]);
		}
	}
	set_heredoc_name(g_arg.cmds[i]);
}

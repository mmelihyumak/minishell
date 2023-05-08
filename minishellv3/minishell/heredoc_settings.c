/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 02:04:40 by melih             #+#    #+#             */
/*   Updated: 2023/05/08 03:28:45 by melih            ###   ########.fr       */
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
	static t_arg_list	*temp;
	int	i;

	i = 0;
	if (temp == NULL)
		temp = g_arg.list;
	while (temp && temp->flag != '|')
	{
		if (temp->flag == 'e')
		{
			command->heredoc[i].here_doc_name = ft_strdup(temp->content);
			i++;
		}
		temp = temp->next;
	}
	if (temp && temp->flag == '|' && temp->next != NULL)
		temp = temp->next;
}

int	check_active_heredoc(void)
{
	return (0);
}

void	set_heredocs(void)
{
	int	i;

	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		count_heredoc(g_arg.cmds[i]);
		g_arg.cmds[i]->heredoc = malloc(sizeof(t_heredoc) * g_arg.cmds[i]->heredoc_count);
		set_heredoc_name(g_arg.cmds[i]);	
	}
}
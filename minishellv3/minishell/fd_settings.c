/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 02:23:13 by melih             #+#    #+#             */
/*   Updated: 2023/05/02 21:06:01 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fds(void)
{
	t_arg_list	*temp;
	int	i;
	int	j;

	i = 0;
	temp = g_arg.list;
	while (g_arg.cmds[i])
	{
		j = 0;
		if (temp->flag == '|' && temp->next != NULL)
			temp = temp->next;
		while (temp)
		{
			if (temp->flag == 'i')
			{
				g_arg.cmds[i]->infile_name = temp->content;
				g_arg.cmds[i]->fd_in = open(temp->content, O_RDONLY);
			}
			else if (temp->flag == 't')
			{
				g_arg.cmds[i]->outfile_name = temp->content;
				g_arg.cmds[i]->fd_out = open(temp->content, O_CREAT | O_TRUNC | O_RDWR, 0777);
			}
			else if (temp->flag == 'h')
				t_here_doc_settings(g_arg.cmds[i]);
			if (temp->flag == '|')
				break ;
			temp = temp->next;
		}
		i++;
	}
}
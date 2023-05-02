/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_s_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:20:33 by melih             #+#    #+#             */
/*   Updated: 2023/05/03 01:34:02 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_cmd_settings(void)
{
	int	i;
	t_arg_list	*temp;
	
	temp = g_arg.list;
	g_arg.cmds = malloc(sizeof(t_cmd *) * (g_arg.pipe_count + 1));
	i = 0;
	while (i < g_arg.pipe_count + 1)
	{
		g_arg.cmds[i] = malloc(sizeof(t_cmd));
		g_arg.cmds[i]->cmd_args = g_arg.commands[i];
		g_arg.cmds[i]->fd_in = 0;
		g_arg.cmds[i]->fd_out = 1;
		while (temp->next)
		{
			if (temp->flag == 'h')
				g_arg.cmds[i]->here_doc_name = temp->next->content;
			temp = temp->next;
		}
		i++;
	}
	g_arg.cmds[i] = NULL;
}

void	t_here_doc_settings(t_cmd *command)
{
	pipe(command->here_doc.tubes);
	command->here_doc.here_doc_name = command->here_doc_name;
	command->fd_in = command->here_doc.tubes[0];
	printf("settings: %s\n", command->here_doc.here_doc_name);
	printf("here doc settings\n");
}

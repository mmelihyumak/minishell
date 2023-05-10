/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_s_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:20:33 by melih             #+#    #+#             */
/*   Updated: 2023/05/09 02:45:15 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_cmd_settings(void)
{
	int	i;
	t_arg_list	*temp;
	
	temp = g_arg.list;
	g_arg.cmds = malloc(sizeof(t_cmd *) * (g_arg.pipe_count + 2));
	i = 0;
	while (i < g_arg.pipe_count + 1)
	{
		g_arg.cmds[i] = malloc(sizeof(t_cmd));
		g_arg.cmds[i]->infile_name = NULL;
		g_arg.cmds[i]->outfile_name = NULL;
		g_arg.cmds[i]->heredoc = NULL;
		g_arg.cmds[i]->cmd_args = g_arg.commands[i];
		g_arg.cmds[i]->fd_in = 0;
		g_arg.cmds[i]->fd_out = 1;
		i++;
	}
	g_arg.cmds[i] = NULL;
}

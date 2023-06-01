/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:56:32 by melih             #+#    #+#             */
/*   Updated: 2023/06/01 22:45:45 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(int i)
{
	int	x;

	printf("exit\n");
	if (split_len(g_arg.cmds[0]->cmd_args) > 2)
	{
		
		printf("minishell: exit: too many arguments\n");
		exit(1);
	}
	else if (split_len(g_arg.cmds[0]->cmd_args) == 2)
	{
		x = -1;
		while (g_arg.cmds[0]->cmd_args[1][++x])
		{
			if (!ft_isdigit(g_arg.cmds[0]->cmd_args[1][x]))
			{
				printf("minishell: %s: numeric argument required\n", g_arg.cmds[0]->cmd_args[1]);
				exit(255);
			}
		}
		exit(ft_atoi(g_arg.cmds[0]->cmd_args[1]));
	}
	else if (split_len(g_arg.cmds[0]->cmd_args) == 1)
		exit (0);
}

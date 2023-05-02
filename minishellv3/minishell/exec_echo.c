/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:23:00 by melih             #+#    #+#             */
/*   Updated: 2023/04/27 17:28:03 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(int j)
{
	int	i;

	if (!ft_strncmp("-n", g_arg.cmds[j]->cmd_args[1], 2) && ft_strlen(g_arg.cmds[j]->cmd_args[1]) == 2)
	{
		i = 2;
		while (!ft_strncmp("-n",  g_arg.cmds[j]->cmd_args[i], 2))
			i++;
		while ( g_arg.cmds[j]->cmd_args[i])
		{
			printf("%s",  g_arg.cmds[j]->cmd_args[i]);
			if ( g_arg.cmds[j]->cmd_args[i + 1] != 0)
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while ( g_arg.cmds[j]->cmd_args[i])
		{
			printf("%s",  g_arg.cmds[j]->cmd_args[i]);
			if ( g_arg.cmds[j]->cmd_args[i + 1] != 0)
				printf(" ");
			i++;
		}
		printf("\n");
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:56:32 by melih             #+#    #+#             */
/*   Updated: 2023/06/01 18:32:03 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(int i)
{
	printf("exit\n");
	if (split_len(g_arg.cmds[0]->cmd_args) > 2)
		printf("minishell: exit: too many arguments\n");
	else
		exit(ft_atoi(g_arg.cmds[0]->cmd_args[1]));
}

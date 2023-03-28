/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 04:03:44 by muyumak           #+#    #+#             */
/*   Updated: 2023/03/28 04:07:54 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(void)
{
	int	len;

	len = split_len(g_arg.envp);
	printf("---: %p\n", g_arg.envp[len]);
	g_arg.envp[len] = malloc(sizeof(char *));
	printf("---: %p\n", g_arg.envp[len]);
}
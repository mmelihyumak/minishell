/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 00:37:40 by muyumak           #+#    #+#             */
/*   Updated: 2023/03/30 08:02:51 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(void)
{
	int	i;

	if (!ft_strncmp("-n", g_arg.args[1], 2) && ft_strlen(g_arg.args[1]) == 2)
	{
		i = 2;
		while (!ft_strncmp("-n", g_arg.args[i], 2))
			i++;
		while (g_arg.args[i])
		{
			printf("%s", g_arg.args[i]);
			if (g_arg.args[i + 1] != 0)
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while (g_arg.args[i])
		{
			printf("%s", g_arg.args[i]);
			if (g_arg.args[i + 1] != 0)
				printf(" ");
			i++;
		}
		printf("\n");
	}
}
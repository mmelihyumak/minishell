/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:56:32 by melih             #+#    #+#             */
/*   Updated: 2023/03/24 04:01:47 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_folder(void)
{
	int	fd;

	fd = open(g_arg.args[1], O_RDWR);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", g_arg.args[1]);
		return (0);
	}
	return (0);
}
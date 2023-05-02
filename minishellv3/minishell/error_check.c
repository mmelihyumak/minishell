/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:57:50 by melih             #+#    #+#             */
/*   Updated: 2023/04/21 02:07:06 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_check(void)
{
	t_arg_list	*last;

	last = g_arg.list;
	while (last->next)
		last = last->next;
	if (last->flag == '|')
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}
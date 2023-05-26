/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:57:50 by melih             #+#    #+#             */
/*   Updated: 2023/05/26 21:28:00 by uyilmaz          ###   ########.fr       */
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

int	check_quote(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
			if (str[i] != c)
			{
				printf("syntax error\n");
				return (1);
			}
		}
	}
	return (0);
}

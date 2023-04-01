/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 04:38:26 by melih             #+#    #+#             */
/*   Updated: 2023/04/02 02:06:01 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_arg(t_arg_list *list)
{
	if (list->flag == '<' || list->flag == '>' || list->flag == '|' || list->is_used == 1) //Here doc ve append eklemesi yapılacak!
		return (1);
	return (0);
}

int	count_cmd_arg(t_arg_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->flag == '<' || list->flag == '>' || list->flag == '|')
			break ;
		i++;
		list = list->next;
	}
	return (i);
}

void	set_cmd_args(t_arg_list *list)
{
	int	len;
	int	i;

	i = 0;
	len = count_cmd_arg(list);
	g_arg.cmd_args = malloc(sizeof(char *) * (len + 1));
	g_arg.will_free = 1;
	while (list)
	{
		if (!check_cmd_arg(list))
		{
			list->is_used = 1;
			g_arg.cmd_args[i] = ft_strdup(list->content);
			i++;
		}
		list = list->next;
	}
	g_arg.cmd_args[i] = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spreader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:37:21 by melih             #+#    #+#             */
/*   Updated: 2023/04/02 02:03:03 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_count(void)
{
	t_arg_list *temp;
	int			i;

	temp = g_arg.list;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	g_arg.arg_count = i;
}

int	pipe_count(void)
{
	t_arg_list *temp;
	int			i;
	int			count;

	temp = g_arg.list;
	i = 0;
	while (i < g_arg.arg_count)
	{
		if (temp->flag == '|')
			count++;
		i++;
	}
	g_arg.pipe_count = count;
	return (count);
}

int	open_infiles(void)
{
	t_arg_list *temp;
	int			i;

	temp = g_arg.list;
	i = 0;
	while (i < g_arg.arg_count)
	{
		if (temp->flag == '<')
			if (open_infile(temp))
				return (1);
		if (temp->flag == '>')
			if (open_outfile(temp))
				return (1);
		temp = temp->next;
		i++;
	}
	return (0);
}

int	check_infiles(void)
{
	t_arg_list *temp;

	temp = g_arg.list;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (0);	
}

int	spreader(void)
{
	t_arg_list	*list;
	int			i;

	list = g_arg.list;
	if (open_infiles())
		return (1);
	i = -1;
	while (list && i < g_arg.pipe_count)
	{
		while (list->next && list->is_used)
			list = list->next;
		if (list->is_used)
			break ;	
		set_cmd_args(list);
		if (list->next)
			list = list->next;
		else
			break ;
		i++;
	}
	cmd_process(g_arg.envp, g_arg.fd_in, g_arg.fd_out);
	return (0);
}
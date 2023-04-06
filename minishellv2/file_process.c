/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:56:32 by melih             #+#    #+#             */
/*   Updated: 2023/04/02 01:58:15 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_arg_list *list)
{
	int	fd;

	if (list->next)
		list = list->next;
	else
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	g_arg.fd_in = open(list->content, O_RDWR);
	list->is_used = 1;
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", list->content);
		return (1);
	}
	if (list->next)
		list = list->next;
	return (0);
}

int	open_outfile(t_arg_list *list)
{
	int	fd;

	if (list->next)
		list = list->next;
	else
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (g_arg.fd_out > 2)
		close(g_arg.fd_out);
	g_arg.fd_out = open(list->content, O_CREAT | O_TRUNC | O_RDWR, 0777);
	list->is_used = 1;
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", list->content);
		return (0);
	}
	if (list->next)
		list = list->next;
	return (0);
}

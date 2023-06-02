/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spreader_utils_v2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:13:10 by muyumak           #+#    #+#             */
/*   Updated: 2023/06/02 10:33:57 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_setter_v2(t_arg_list **temp)
{
	if (ft_strcmp((*temp)->content, "<<") == 0 && (*temp)->flag == '<')
	{
		(*temp)->flag = 'h';
		if ((*temp)->next && (*temp)->next->flag == 'i')
			(*temp)->next->flag = 'e';
		else
		{
			printf("minishell: syntax error near unexpected token %s\n",
				(*temp)->content);
			return (1);
		}
	}
	if (ft_strcmp((*temp)->content, ">>") == 0 && (*temp)->flag == '>')
	{
		(*temp)->flag = 'a';
		if ((*temp)->next && (*temp)->next->flag == 't')
			(*temp)->next->flag = 'p';
		else
		{
			printf("minishell: syntax error near unexpected token %s\n",
				(*temp)->content);
			return (1);
		}
	}
	return (0);
}

int	flag_setter_v3(t_arg_list **temp)
{
	if ((*temp)->flag == '>')
	{
		if ((*temp)->next && (*temp)->next->flag == 'o')
			(*temp)->next->flag = 't';
		else
		{
			printf("minishell: syntax error near unexpected token %s\n",
				(*temp)->content);
			return (1);
		}
	}
	if ((*temp)->flag == '<')
	{
		if ((*temp)->next && (*temp)->next->flag == 'o')
			(*temp)->next->flag = 'i';
		else
		{
			printf("minishell: syntax error near unexpected token %s\n",
				(*temp)->content);
			return (1);
		}
	}
	return (0);
}

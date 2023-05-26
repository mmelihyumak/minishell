/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:21:19 by melih             #+#    #+#             */
/*   Updated: 2023/05/25 21:37:59 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_in_export(void)
{
	int	i;

	i = -1;
	while (g_arg.exports[++i])
	{
		if (!ft_strncmp(g_arg.exports[i], g_arg.cmds[0]->cmd_args[1],
			ft_strlen(g_arg.cmds[0]->cmd_args[1])))
			return (i);
	}
	return (-1);
}

int	find_in_env(void)
{
	int	i;

	i = -1;
	while (g_arg.env[++i])
	{
		if (!ft_strncmp(g_arg.env[i], g_arg.cmds[0]->cmd_args[1],
			ft_strlen(g_arg.cmds[0]->cmd_args[1])))
			return (i);
	}
	return (-1);
}

void	ft_delete_env(void)
{
	int	index;
	int	len;
	int	i;
	int	j;
	char	**temp;

	index = find_in_env();
	if (index == -1)
		return ;
	len = split_len(g_arg.env);
	temp = malloc(sizeof(char *) * (len + 1));
	i = -1;
	j = -1;
	while (++i < len)
	{
		if (i == index)
			j++;
		temp[i] = ft_strdup(g_arg.env[++j]);
	}
	temp[i] = 0;
	free_split(g_arg.env);
	printf("address env: %p\n", g_arg.env);
	g_arg.env = temp;
}

void	ft_delete_export(void)
{
	int	index;
	int	len;
	int	i;
	int	j;
	char	**temp;

	index = find_in_export();
	if (index == -1)
		return ;
	len = split_len(g_arg.exports);
	temp = malloc(sizeof(char *) * (len + 1));
	i = -1;
	j = -1;
	while (++i < len)
	{
		if (i == index)
			j++;
		temp[i] = ft_strdup(g_arg.exports[++j]);
	}
	temp[i] = 0;
	free_split(g_arg.exports);
	g_arg.exports = temp;
}

void	exec_unset(void)
{
	ft_delete_export();
	ft_delete_env();
}

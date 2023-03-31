/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 04:37:37 by melih             #+#    #+#             */
/*   Updated: 2023/03/30 05:29:17 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char **envp)
{
	int	variable_count;
	int	i;

	variable_count = split_len(envp);
	g_arg.envp = malloc(sizeof(char *) * (variable_count + 1));
	i = -1;
	while (envp[++i])
	{
		g_arg.envp[i] = ft_strdup(envp[i]);
	}
}

void	set_export(void)
{
	int	variable_count;
	int	i;

	variable_count = split_len(g_arg.envp);
	g_arg.exports = malloc(sizeof(char *) * (variable_count + 1));
	i = -1;
	while (g_arg.envp[++i])
	{
		g_arg.exports[i] = ft_strjoin("declare -x ", g_arg.envp[i]);
	}
}
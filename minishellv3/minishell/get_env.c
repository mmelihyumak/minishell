/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:47:34 by melih             #+#    #+#             */
/*   Updated: 2023/04/29 04:07:08 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_len(char **strings)
{
	int	i;

	if (!strings)
		return (-1);
	i = 0;
	while (strings[i])
		i++;
	return (i);
}

void	get_env(char **envp)
{
	int	len;
	int	i;

	len = split_len(envp);
	g_arg.env = malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (envp[++i])
		g_arg.env[i] = ft_strdup(envp[i]);
	g_arg.env[i] = 0;
}

void	exec_pwd(void)
{
	int	i;

	i = -1;
	while (g_arg.env[++i])
	{
		if (!ft_strncmp("PWD", g_arg.env[i], 3))
			printf("%s\n", g_arg.env[i]);
	}
}

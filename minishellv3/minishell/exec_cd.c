/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 03:49:17 by melih             #+#    #+#             */
/*   Updated: 2023/05/03 17:43:32 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_back(char *env_pwd)
{
	int	i;

	i = ft_strlen(env_pwd) - 1;
	while (env_pwd[i] && env_pwd[i] != '/')
	{
		env_pwd[i] = 0;
		i--;
	}
	env_pwd[i] = 0;
	chdir(env_pwd);
}

void	exec_cd(int query)
{
	char	*env_pwd;
	
	env_pwd = g_arg.pwd;
	if (g_arg.cmds[query]->cmd_args[1] == 0)
	{
		g_arg.pwd = getenv("HOME");
		chdir(getenv("HOME"));
	}
	else if (!ft_strncmp("..", g_arg.cmds[query]->cmd_args[1], ft_strlen(g_arg.cmds[query]->cmd_args[1])))
		go_back(g_arg.pwd);
	else
	{
		g_arg.pwd = ft_strjoin(g_arg.pwd, "/");
		g_arg.pwd = ft_strjoin(g_arg.pwd, g_arg.cmds[query]->cmd_args[1]);
		if (!access(g_arg.pwd, F_OK))
			chdir(g_arg.pwd);
		else
			go_back(g_arg.pwd);
	}
}

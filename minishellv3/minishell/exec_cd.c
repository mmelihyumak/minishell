/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 03:49:17 by melih             #+#    #+#             */
/*   Updated: 2023/04/30 18:34:16 by melih            ###   ########.fr       */
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
	
	printf("cd_cmd: -%s-\n",  g_arg.cmds[query]->cmd_args[0]);
	env_pwd = g_arg.pwd;
	if (g_arg.cmds[query]->cmd_args[1] == 0)
	{
		g_arg.pwd = getenv("HOME");
		int x = chdir(getenv("HOME"));
		printf("chdir: --%d--\n", x);
	}
	else if (!ft_strncmp("..", g_arg.cmds[query]->cmd_args[1], ft_strlen(g_arg.cmds[query]->cmd_args[1])))
		go_back(g_arg.pwd);
	else
	{
		g_arg.pwd = ft_strjoin(g_arg.pwd, "/");
		g_arg.pwd = ft_strjoin(g_arg.pwd, g_arg.cmds[query]->cmd_args[1]);
		chdir(g_arg.pwd);
	}
	g_arg.pwd = getcwd(g_arg.pwd, 1000);
	printf("g_arg.pwd: %s\n", g_arg.pwd);
	//system("leaks minishell");
}

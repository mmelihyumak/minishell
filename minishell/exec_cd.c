/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 02:29:01 by muyumak           #+#    #+#             */
/*   Updated: 2023/03/31 04:57:45 by melih            ###   ########.fr       */
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

void	exec_cd(void)
{
	static char	*env_pwd;
	
	if (!env_pwd)
		env_pwd = getenv("PWD");
	if (g_arg.args[1] == 0)
	{
		env_pwd = getenv("HOME");
		chdir(getenv("HOME"));
	}
	else if (!ft_strncmp("..", g_arg.args[1], 2))
		go_back(env_pwd);
	else
	{
		env_pwd = ft_strjoin(env_pwd, "/");
		env_pwd = ft_strjoin(env_pwd, g_arg.args[1]);
		chdir(env_pwd);
	}
	system("leaks minishell");
}

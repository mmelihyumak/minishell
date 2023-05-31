/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muyumak <muyumak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 03:49:17 by melih             #+#    #+#             */
/*   Updated: 2023/05/31 18:25:56 by muyumak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(void)
{
	char	*home;
	int		index;
	int		i;
	int		j;
	
	index = check_envp("HOME");
	home = malloc(sizeof(char) * (ft_strlen(g_arg.env[index] + 5) + 1));
	i = 4;
	j = -1;
	while (g_arg.env[index][++i])
		home[++j] = g_arg.env[index][i];
	home[j + 1] = 0;
	return (home);
}

void	exec_cd(int query)
{
	char	*cwd;
	char	*temp;
	
	if ((split_len(g_arg.cmds[0]->cmd_args) == 2
		&& !ft_strcmp("~", g_arg.cmds[0]->cmd_args[1])
		|| split_len(g_arg.cmds[0]->cmd_args) == 1))
	{
		temp = get_home();
		chdir(temp);
		free(temp);
	}
	else if (split_len(g_arg.cmds[0]->cmd_args) == 2)
	{
		if (g_arg.cmds[0]->cmd_args[1][0] == '~')
		{
			temp = get_variable("HOME");
			temp = ft_strjoin(temp, &g_arg.cmds[0]->cmd_args[1][1]);
			chdir(temp);
			free(temp);
		}
		else
			chdir(g_arg.cmds[0]->cmd_args[1]);
	}
	cwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(cwd, PATH_MAX);
	temp = ft_strjoin("PWD=", cwd);
	put_env(temp);
	free(temp);
	free(cwd);
}

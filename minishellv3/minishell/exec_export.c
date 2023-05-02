/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 23:41:47 by melih             #+#    #+#             */
/*   Updated: 2023/04/27 23:50:28 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_export(void)
{
	int	variable_count;
	int	i;

	variable_count = split_len(g_arg.env);
	g_arg.exports = malloc(sizeof(char *) * (variable_count + 1));
	i = -1;
	while (g_arg.env[++i])
		g_arg.exports[i] = ft_strjoin("declare -x ", g_arg.env[i]);
}

int	ft_strlen_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

int	check_envp(char *value)
{
	int	i;

	i = 0;
	while (g_arg.env[i])
	{
		if (!ft_strncmp(g_arg.env[i], value, ft_strlen_equal(value)))
		{
			if (!ft_strncmp(g_arg.env[i], value, ft_strlen(value)))
				return (1);
			else
				break ;
		}
		i++;
	}
	i = 0;
	while (g_arg.exports[i])
	{
		if (!ft_strncmp(&g_arg.exports[i][11], value, ft_strlen_equal(value)))
		{
			if (!ft_strncmp(&g_arg.exports[i][11], value, ft_strlen(value)))
				return (1);
			else
			{
				put_export(value, i, 0);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	exec_export(int	query)
{
	int	i;
	int	j;

	if (g_arg.cmds[query]->cmd_args[1] == 0)
	{
		i = -1;
		while (g_arg.exports[++i])
			ft_smart_putstr(g_arg.exports[i]);
	}
	else
	{
		j = 0;
		i = split_len(g_arg.env);
		while (g_arg.cmds[query]->cmd_args[++j])
		{
			if (!check_envp(g_arg.cmds[query]->cmd_args[j]))
			{
				if (!equal_control(g_arg.cmds[query]->cmd_args[j]))
				{
					g_arg.env[i] = ft_strdup(g_arg.cmds[query]->cmd_args[j]);
					i++;
					g_arg.env[i] = malloc(sizeof(char *));
					g_arg.env[i] = 0;
					put_export(g_arg.cmds[query]->cmd_args[j], split_len(g_arg.exports), 1);
				}
				else
				{
					put_export(g_arg.cmds[query]->cmd_args[j], split_len(g_arg.exports), 1);
				/*	i = split_len(g_arg.exports);
					free(g_arg.exports[i]);
					g_arg.exports[i] = ft_strjoin("declare -x ", g_arg.args[j]);
					i++;
					g_arg.exports[i] = malloc(sizeof(char *));
					g_arg.exports[i] = 0;*/
				}
			}
		}
	}
}

int	equal_control(char *arg)
{
	int	i;

	i= -1;
	while (arg[++i])
		if (arg[i] == '=')
			return (0);
	return (1);
}

void	exec_env(void)
{
	int	i;

	i = -1;
	while (g_arg.env[++i])
		printf("%s\n", g_arg.env[i]);
}

void	put_export(char *arg, int i, int flag)
{
	free(g_arg.exports[i]);
	g_arg.exports[i] = ft_strjoin("declare -x ", arg);
	if (flag == 1)
	{
		i++;
		g_arg.exports[i] = malloc(sizeof(char *));
		g_arg.exports[i] = 0;
	}
}

void	ft_smart_putstr(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			printf("=");
			printf("%c", 34);
		}
		else
			printf("%c", arg[i]);
	}
	if (!equal_control(arg))
		printf("%c", 34);
	printf("\n");
}

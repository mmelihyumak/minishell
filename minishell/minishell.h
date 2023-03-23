/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:46 by melih             #+#    #+#             */
/*   Updated: 2023/03/23 02:31:10 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "./libft/libft.h"

struct s_arg
{
	pid_t	pid;
	char	*cmd;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	**args;
	int		quit_flag;
}	g_arg;

char	*find_path(char **envp);
char	*get_cmd(char **paths, char *cmd);
int		cmd_process(char **envp, char *input);
void	sigquit_voider(int signal);
void	eof_control(char *line);
void	sigint_voider(int signal);

#endif
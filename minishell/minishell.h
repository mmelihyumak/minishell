/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:46 by melih             #+#    #+#             */
/*   Updated: 2023/03/30 11:09:02 by melih            ###   ########.fr       */
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
# include <dirent.h>
# include "./libft/libft.h"

struct s_arg
{
	pid_t	pid;
	char	*cmd;
	char	*pwd;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	**args_temp;
	char	**args;
	char	**envp;
	char	**exports;
	int		quit_flag;
}	g_arg;

char	*find_path(char **envp);
char	*get_cmd(char **paths, char *cmd);
int		cmd_process(char **envp);
void	sigquit_voider(int signal);
void	eof_control(char *line);
void	sigint_voider(int signal);
char	*find_pwd(char **envp);
char	**ft_split_quotes(char *str);
void	exec_echo(void);
void	exec_cd(void);
int		split_len(char **split);
void	exec_export(void);
void	set_env(char **envp);
void	set_export(void);
void	put_export(char *arg, int i, int flag);
void	exec_env(void);
int		check_envp(char *value);
int		ft_strlen_equal(char *arg);
void	ft_smart_putstr(char *arg);
int		equal_control(char *arg);

#endif
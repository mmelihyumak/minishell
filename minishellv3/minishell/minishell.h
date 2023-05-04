/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:46 by melih             #+#    #+#             */
/*   Updated: 2023/05/03 17:36:53 by melih            ###   ########.fr       */
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

typedef struct s_here_doc
{
	pid_t	pid;
	int		tubes[2];	
	char	*here_doc_name;
}	t_here_doc;

typedef struct s_arg_list
{
	char				*content;
	char				flag;
	struct s_arg_list	*next;
}	t_arg_list;

typedef struct s_cmd
{
	char			**cmd_args;
	char			*infile_name;
	char			*outfile_name;
	int				fd_in;
	int				fd_out;
	char			*here_doc_name;
	int				query;
	t_here_doc		here_doc;
}	t_cmd;

struct s_arg
{
	pid_t		*pid;
	pid_t		heredoc_pid;
	char		quote_flag;
	char		*input;
	char		*here_doc_input;
	char		*cmd;
	char		*pwd;
	char		*paths;
	char		**cmd_paths;
	char		**cmd_args;
	char		**args_temp;
	//char		**args;
	char		**env;
	char		**exports;
	char		***commands;
	int			quit_flag;
	int			arg_count;
	int			pipe_count;
	int			cmd_index;
	int			exit_status;
	int			**tubes;
	t_cmd		**cmds;
	t_arg_list	*list;
}	g_arg;

char		*find_path(char **envp);
char		*get_cmd(char **paths, char *cmd);
int			cmd_process(char **envp, int i, int j);
void		sigquit_voider(int signal);
void		eof_control(char *line);
void		sigint_voider(int signal);
char		*find_pwd(char **envp);
void		ft_lstdelone_v2(t_arg_list **lst);
void		ft_lstclear_v2(t_arg_list **lst);
t_arg_list	*ft_lstnew_v2(char *content, char flag);
void		ft_lstadd_back_v2(t_arg_list **lst, t_arg_list *new);
int			list_init(char *str);
char		*ft_strjoin_v3(char *s1, char *s2);
char		*ft_strdup_v2(char *str, int start, int end);
char		*ft_strdup_v3(char *str, int *start, char end);
int			is_it_special(char c);
char		*get_env_var(char *str, char **env, int *i, int *j);
int			ft_strlen_v2(char *str, char q, int i);
void		count_arg(void);
void		refresh_counts(void);
void		spreader(void);
void		open_pipes(void);
int			count_cmd_arg(t_arg_list *temp);
int			flag_setter(void);
void		free_split(char **strings);
void		t_cmd_settings(void);
void		free_commands(void);
void		set_fds(void);
int			pipe_check(void);
void		set_tubes(void);
void		close_tubes(void);
void		wait_process(void);
void		close_fd(t_cmd *command);
void		get_env(char **envp);
int			split_len(char **strings);
void		exec_pwd(void);
int			executor(int i);
void		exec_echo(int j);
int			ft_strlen_equal(char *arg);
int			check_envp(char *value);
void		exec_export(int	query);
int			equal_control(char *arg);
void		put_export(char *arg, int i, int flag);
void		ft_smart_putstr(char *arg);
void		set_export(void);
void		exec_cd(int query);
void		go_back(char *env_pwd);
int			here_doc_process(t_cmd *command);
void		t_here_doc_settings(t_cmd *command);
char		*ft_strjoin_v2(char *str, char *buff);


void	print_input(char **strings);
void	print_t_cmd(void);
void	print_closing_fd(int fd);

#endif
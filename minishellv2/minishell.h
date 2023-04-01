/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:46 by melih             #+#    #+#             */
/*   Updated: 2023/04/02 02:01:39 by melih            ###   ########.fr       */
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

typedef struct s_arg_list
{
	char				*content;
	char				flag;
	int					is_used;
	struct s_arg_list	*next;
}	t_arg_list;

struct s_arg
{
	pid_t		pid;
	char		quote_flag;
	char		*cmd;
	char		*pwd;
	char		*paths;
	char		**cmd_paths;
	char		**cmd_args;
	char		**args_temp;
	char		**args;
	char		**envp;
	int			quit_flag;
	int			fd_in;
	int			fd_out;
	int			arg_count;
	int			pipe_count;
	int			will_free;
	t_arg_list	*list;
}	g_arg;

char		*find_path(char **envp);
char		*get_cmd(char **paths, char *cmd);
int			cmd_process(char **envp, int fd_in, int fd_out);
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
int			spreader(void);
int			open_infile(t_arg_list *list);
int			open_outfile(t_arg_list *list);
int			split_len(char **split);
void		get_envp(char **envp);
void		set_cmd_args(t_arg_list *list);
int			count_cmd_arg(t_arg_list *list);
int			check_cmd_arg(t_arg_list *list);
void		arg_count(void);
void		free_split(char **splitted);
int			pipe_count(void);

#endif
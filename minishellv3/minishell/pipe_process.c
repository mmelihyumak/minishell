/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:39:47 by melih             #+#    #+#             */
/*   Updated: 2023/05/05 05:37:47 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipes(void)
{
	int	i;

	i = 0;
	g_arg.tubes = malloc(sizeof(int *) * g_arg.pipe_count);
	while (i < g_arg.pipe_count)
	{
		g_arg.tubes[i] = malloc(sizeof(int) * 2);
		pipe(g_arg.tubes[i]);
		i++;
	}
}

void	set_tubes(void)
{
	int	i;

	i = 0;
	while (i < g_arg.pipe_count)
	{
		g_arg.cmds[i]->fd_out = g_arg.tubes[i][1];
		i++;
	}
	i = 1;
	while (i < g_arg.pipe_count + 1)
	{
		g_arg.cmds[i]->fd_in = g_arg.tubes[i - 1][0];
		i++;
	}
}

void	close_tubes(void)
{
	int	i;

	i = 0;
	while (i < g_arg.pipe_count)
	{
		printf("closing in: %d\n", g_arg.tubes[i][0]);
		printf("closing out: %d\n", g_arg.tubes[i][1]);
		close(g_arg.tubes[i][1]);
		close(g_arg.tubes[i][0]);
		i++;
	}
	i = -1;
	while (++i < g_arg.pipe_count + 1)
	{
		if (g_arg.cmds[i]->infile_name != 0)
		{
			printf("infile_name: %s\n", g_arg.cmds[i]->infile_name);
			print_closing_fd(g_arg.cmds[i]->fd_in);
			close(g_arg.cmds[i]->fd_in);
		}
		if (g_arg.cmds[i]->outfile_name != 0)
		{
			printf("outfile_name: %s\n", g_arg.cmds[i]->outfile_name);
			print_closing_fd(g_arg.cmds[i]->fd_out);
			close(g_arg.cmds[i]->fd_out);
		}
		if (g_arg.cmds[i]->here_doc.here_doc_name)
		{
			printf("here_doc.tubes[1]: %d\n", g_arg.cmds[i]->here_doc.tubes[1]);
			print_closing_fd(g_arg.cmds[i]->here_doc.tubes[0]);
			print_closing_fd(g_arg.cmds[i]->here_doc.tubes[1]);
			close(g_arg.cmds[i]->here_doc.tubes[0]);
			close(g_arg.cmds[i]->here_doc.tubes[1]);
		}
	}
}

void	close_fd(t_cmd *command)
{
	int	i;
	
	i = 0;
	while (i < g_arg.pipe_count)
	{
		if (command->fd_in != g_arg.tubes[i][0] && !command->here_doc.here_doc_name)
		{
			printf("content: %s\n", command->cmd_args[0]);
			printf("fd_in: %d\n", g_arg.tubes[i][0]);
			close(g_arg.tubes[i][0]);
			print_closing_fd(g_arg.tubes[i][0]);
		}
		if (command->fd_out != g_arg.tubes[i][1])
		{
			printf("content: %s\n", command->cmd_args[0]);
			printf("fd_out: %d\n", g_arg.tubes[i][1]);
			close(g_arg.tubes[i][1]);
			print_closing_fd(g_arg.tubes[i][1]);
		}
		i++;
	}
	printf("last: ");
	print_closing_fd(command->here_doc.tubes[1]);
	close(command->here_doc.tubes[1]);
}

void	wait_process(void)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < g_arg.pipe_count + 1)
	{
		waitpid(g_arg.pid[i], &g_arg.exit_status, 0);
		if (WIFEXITED(g_arg.exit_status))
		{
			g_arg.exit_status = WEXITSTATUS(g_arg.exit_status);
			printf("status: %d\n", g_arg.exit_status);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 02:20:29 by melih             #+#    #+#             */
/*   Updated: 2023/03/23 02:30:26 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **envp)
{
	t_arg	*arg;
	char	*input;

	arg = malloc(sizeof(t_arg));
	arg->paths = find_path(envp);
	arg->cmd_paths = ft_split(arg->paths, ':');
	while (1)
	{
		input = readline("minishell: ");
		add_history(input);
		arg->args = ft_split(input, ' ');
		cmd_process(arg, envp, input);
		
	}
	return (0);
}

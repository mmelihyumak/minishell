/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:58:23 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/04/07 02:09:35 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_special(char c)
{
	if (c == ' ' || c == 9 || c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

char	*get_env_var(char *str, char **env, int *i, int *j)
{
	int	index;
	int	len;

	index = 0;
	while (ft_isalnum(str[index]))
			index++;
	*j = *i;
	*i += index;
	len = *i - *j;
	while (*env)
	{
		if (ft_strncmp(str, *env, len) == 0 && (*env)[len] == '=')
			break ;
		env++;
	}
	if (!(*env))
		return (NULL);
	return (ft_strdup(&((*env)[len + 1])));
}

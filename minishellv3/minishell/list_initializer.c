/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:58:05 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/04/27 15:48:53 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_handler(char *str, char q)
{
	int		i;
	int		j;
	char	*result;
	char	*env;

	if (q == 39)
		return (str);
	result = NULL;
	i = 0;
	while (str[i])
	{
		j = i;
		while (str[i] && str[i] != '$')
			i++;
		result = ft_strjoin_v3(result, ft_strdup_v2(str, j, i));
		if (str[i] == '$')
		{
			env = get_env_var(&str[++i], g_arg.env, &i, &j);
			if (env)
				result = ft_strjoin_v3(result, env);
		}
	}
	free(str);
	return (result);
}

char	*handle_regular(char *str, int *index)
{
	int		i;
	char	*result;

	i = *index;
	while (str[i] && !is_it_special(str[i]) && str[i] != 34 && str[i] != 39)
		i++;
	result = ft_strdup_v2(str, *index, i);
	*index = i;
	return (result);
}

void	handle_others(char *str, int *index, char q)
{
	int		i;
	int		flag;
	char	*result;

	result = NULL;
	i = *index;
	while (str[i] && !is_it_special(str[i]))
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i++;
			result = ft_strjoin_v3(result, dollar_handler
					(ft_strdup_v3(str, &i, str[i - 1]), str[i - 1]));
		}
		else
			result = ft_strjoin_v3(result,
					dollar_handler(handle_regular(str, &i), 0));
	}
	ft_lstadd_back_v2(&g_arg.list, ft_lstnew_v2(result, 'o'));
	*index = i;
}

void	special_handler(char *str, int *index, char q)
{
	int		backup;
	int		i;
	char	*result;

	backup = *index;
	i = 1;
	if (str[i + backup] == q && str[i + backup] != '|')
		i++;
	result = ft_strdup_v2(str, backup, i + backup);
	ft_lstadd_back_v2(&g_arg.list, ft_lstnew_v2(result, q));
	*index = i + backup;
}

int	list_init(char *str)
{
	char	*result;
	int		len;
	int		i;

	len = ft_strlen(str);
	i = 0;
	ft_lstclear_v2(&g_arg.list);
	while (i < len)
	{
		while (str[i] == ' ' || str[i] == 9)
			i++;
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			special_handler(str, &i, str[i]);
		else if (str[i] && str[i] != ' ')
			handle_others(str, &i, 'o');
	}
	t_arg_list *ptr = g_arg.list;
	while (ptr)
	{
		printf("command: #%s#\nflag: %c\n\n", ptr->content, ptr->flag);
		ptr = ptr->next;
	}
	//system("leaks minishell");
	return (0);
}
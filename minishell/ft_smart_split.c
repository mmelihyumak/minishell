/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smart_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 01:30:53 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/03/26 04:25:53 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_control(char *str)
{
	size_t	i;
	int		c;

	i = 0;
	c = -1;
	while (str[i])
	{
		if (str[i] == c)
			return (c);
		if (c == -1 && (str[i] == 34 || str[i] == 39))
			c = str[i];
		i++;
	}
	return (0);
}

int	check_special_arg()
{
	return (0);
}

size_t	word_counter(const char *str, char c, int flag)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	flag = 1;
	while (str[++i])
	{
		if (str[i] == c)
		{
			i++;
			while (str[i] != c)
				i++;
		}
		if (str[i] != ' ' && flag == 1)
		{
			count++;
			flag = 0;
		}
		else if (str[i] == ' ')
			flag = 1;
	}
	return (count);
}

int	word_len(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == c)
	{
		i++;
		while (str[i] != c)
		{
			i++;
			count++;
		}
		i++;
		if (str[i] != ' ')
		{
			while (str[i] && str[i] != ' ')
			{
				if (str[i] != c)
					count++;
				i++;
			}
		}
		return (count);
	}
	while (str[i] != ' ' && str[i])
	{
		if (str[i] != c)
			count++;
		i++;
	}
	return (count);
}

char	*stringer(char **ptr, char c)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * word_len(*ptr, c) + 1);
	i = 0;
	if (**ptr == c)
	{
		(*ptr)++;
		while (**ptr != c)
		{
			ret[i++] = **ptr;
			(*ptr)++;
		}
		(*ptr)++;
		while (**ptr && **ptr != ' ')
		{
			if (**ptr != c)
				ret[i++] = **ptr;
			(*ptr)++;
		}
	}
	else
	{
		while (**ptr && **ptr != ' ')
		{
			if (**ptr == c)
				(*ptr)++;
			ret[i] = **ptr;
			i++;
			(*ptr)++;
		}
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_split_quotes(char *str)
{
	char	**result;
	int		c;
	size_t	size;
	size_t	j;

	c = quotes_control(str);
	if (!str)
		return (NULL);
	size = word_counter(str, c, 0);
	//printf("size: %d\n", size);
	result = malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	j = -1;
	while (++j < size && *str)
	{
		while (*str == ' ')
			str++;
		result[j] = stringer(&str, c);
		while (*str != ' ' && *str)
			str++;
	}
	result[j] = NULL;
	return (result);
}

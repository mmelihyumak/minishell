/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_v2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:35:44 by melih             #+#    #+#             */
/*   Updated: 2023/05/03 17:36:35 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_v2(char *str, char *buff)
{
	char	*strlink;
	int		i;
	int		j;

	if (!str)
	{
		str = malloc(1);
		str[0] = 0;
	}
	if (!str || !buff)
		return (0);
	strlink = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(buff) + 1));
	if (!strlink)
		return (0);
	i = -1;
	if (str)
		while (str[++i])
			strlink[i] = str[i];
	j = 0;
	while (buff[j])
		strlink[i++] = buff[j++];
	strlink[ft_strlen(str) + ft_strlen(buff)] = 0;
	free(str);
	return (strlink);
}

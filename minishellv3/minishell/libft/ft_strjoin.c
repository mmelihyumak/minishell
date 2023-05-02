/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melih <melih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:10:51 by muyumak           #+#    #+#             */
/*   Updated: 2023/03/25 06:49:51 by melih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strlink;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	strlink = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!strlink)
		return (NULL);
	while (s1[i])
	{
		strlink[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strlink[i] = s2[j];
		i++;
		j++;
	}
	strlink[i] = 0;
	return (strlink);
}

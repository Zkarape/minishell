/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:20:02 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/18 19:40:42 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2, int start, int end)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc((ft_strlen(s1) + start - end) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		dst[i] = s1[i];
		i++;
	}
	while (end < start)
	{
		dst[i] = s2[end];
		i++;
		end++;
	}
	dst[i] = '\0';
	return (dst);
}

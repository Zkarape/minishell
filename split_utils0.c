/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:52:10 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/22 19:52:14 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	char	*dst;

	dst = malloc(ft_strlen(s1) + 1);
	if (dst == NULL)
		return (NULL);
	dst[ft_strlen(s1)] = '\0';
	return (ft_memcpy(dst, s1, ft_strlen(s1)));
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	char	*src_temp;
	char	*dest_temp;
	size_t	i;

	src_temp = (char *)src;
	dest_temp = (char *)dest;
	i = 0;
	while (i < n)
	{
		dest_temp[i] = src_temp[i];
		i++;
	}
	return (dest_temp);
}

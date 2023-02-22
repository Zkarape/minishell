/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:02:39 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/27 19:03:04 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_alloc(char **split, char *str, int index)
{
	if (str)
		return (0);
	while (index >= 0)
		free(split[index--]);
	free(split);
	return (1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;

	s = b;
	while (len)
	{
		*s = c;
		s++;
		len--;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

size_t	ft_strlcpy(char *dest, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

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

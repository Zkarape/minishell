/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:20:02 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/26 20:01:16 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
		;
	return (i);
}

char	*str_return_trimmed(char *s, int start, int end, char *val)
{
	char	*dst;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = -1;
//	printf("s[0] == %c\n", s[0]);
	len = ft_strlen(s) - end + start + ft_strlen(val);
	dst = malloc(sizeof(char) * len);
	while (++i < start)
		dst[i] = s[i];
	while (val && val[++j])
		dst[i++] = val[j];
	while (s[end])
	{
		dst[i] = s[end];
		end++;
		i++;
	} 
	dst[i] = '\0';
//	printf("dest == %s", dst);
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2, int start, int end)
{
	int		i;
	int 	len;
	char	*dst;

	i = 0;
	len = ft_strlen(s1);
	if (start == end)
		--len;
	dst = (char *)malloc((ft_strlen(s1) + start - end) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < len)
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

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && ((unsigned char)s1[i] || (unsigned char)s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

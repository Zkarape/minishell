/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joins.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:36:24 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/20 15:54:16 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_m(char *s1, char *s2)
{
	char	*join;
	int		i;

	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		join[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		join[i] = *s2;
		s2++;
		i++;
	}
	join[i] = '\0';
	return (join);
}

char	*ft_strjoin(char *s1, char *s2, t_args *a)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc((a->len + a->start - a->end + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < a->len)
	{
		dst[i] = s1[i];
		i++;
	}
	while (a->end < a->start && s2)
	{
		dst[i] = s2[a->end];
		i++;
		a->end++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*str12;
	char	*str123;

	str12 = ft_strjoin_m(str1, str2);
	str123 = ft_strjoin_m(str12, str3);
	free(str12);
	return (str123);
}

char	*ft_strjoin2(char *s1, char *s2, int start, int end)
{
	int		i;
	char	*dst;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	dst = (char *)malloc((len + start - end + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1 && i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	while (end < start && s2)
	{
		dst[i] = s2[end];
		i++;
		end++;
	}
	dst[i] = '\0';
	if (s1)
		free(s1);
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:45:39 by aivanyan          #+#    #+#             */
/*   Updated: 2022/12/01 17:42:33 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count(char const *s, char c)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

int	ft_count(char *s, char c, char quote)
{
	int	i;

	i = 0;
	while (s[i])
	{
		
	}
}

char const	*ft_start(char const *s, char c)
{
	while (*s)
	{
		if (*s != c)
			return (s);
		s++;
	}
	return (NULL);
}

char const	*ft_end(char const *s, char c)
{
	while (*s)
	{
		if (*s != c && ((*(s + 1) == c) || (*(s + 1) == '\0')))
			return (s);
		s++;
	}
	return (NULL);
}

int	ft_check_alloc(char **split, char *str, int index)
{
	if (str)
		return (0);
	while (index >= 0)
		free(split[index--]);
	free(split);
	return (1);
}

//int	searching_quotes(int move, char const *s, char c)
//{
//	int		i;
//	int		j;
//
//	i = -1;
//	j = -1;
//	while (++i < move)
//	{
//		if (s[i] == c)
//		{
//			j = i + 1;
//			while (j < move && s[j] != c)
//				j++;
//			if (s[j - 1] == c)
//				return (1);
//		}
//	}
//	return (0);
//}

int	searching_for_quotes(char *s, char c, char quote)
{
	int	i;

	i = 0;
	while ()
	{
		
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		count;
	int		i;
	int		end;

	count = ft_count(s, c);
	split = ft_calloc((count + 1), sizeof(s));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		s = ft_start(s, c);
		end = ft_end(s, c) - s + 1;
		split[i] = malloc((end + 1) * sizeof(char));
		if (ft_check_alloc(split, split[i], i))
			return (NULL);
		ft_strlcpy(split[i++], s, end + 1);
		s += end;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrosy <vpetrosy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 19:10:18 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/07 20:37:05 by vpetrosy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\f'
		|| c == '\n' || c == '\r' || c == '\v');
}

size_t	word_count(char *str)
{
	int		i;
	size_t	count;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_is_space(str[i]))
		{
			while (str[i] && !ft_is_space(str[i]))
			{
				if (str[i] == '"' || str[i] == '\'')
					i += find_last_quote(&str[i], str[i]);
				i++;
			}
			count++;
		}
		if (!str[i])
			break ;
		i++;
	}
	return (count);
}

int		word_cpy(char *s_m, char *s, char quote)
{
	int	i;

	i = 0;
	while (s[++i])
	{
		s_m[i] = s[i];
		if (s[i] == quote)
		{
			s_m[i] = s[i];
			return (i);
		}
	}
	return (0);
}

char	*word_allocate(char *str)
{
	int			i;
	char		*str_malloc;

	i = 0;
	while (str[i] && !ft_is_space(str[i]))
	{
		if (str[i] == '"' || str[i] == '\'')
			i += find_last_quote(&str[i], str[i]);
		i++;
	}
	str_malloc = (char *)malloc(sizeof(char) * (i + 1));
	if (!str_malloc)
		return (NULL);
	i = 0;
	while (str[i] && !ft_is_space(str[i]))
	{
		str_malloc[i] = str[i];
		if (str[i] == '"' || str[i] == '\'')
			i += word_cpy(&str_malloc[i], &str[i], str[i]);
		i++;
	}
	str_malloc[i] = '\0';
	return (str_malloc);
}

char	**ft_split(char *str)
{
	size_t	i;
	char	**arr;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * (word_count(str) + 1));
	if (!arr)
		return (NULL);
	while (*str)
	{
		while (*str && ft_is_space(*str))
			str++;
		if (*str && !ft_is_space(*str))
		{
			arr[i] = word_allocate(str);
			if (!arr[i++])
				return (NULL);
		}
		while (*str && !ft_is_space(*str))
		{
			if (*str == '"' || *str == '\'')
				str += find_last_quote(str, *str);
			str++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:05:44 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/03 18:01:44 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

char	*quote_detection(char c)
{
	char	*q;

	q = malloc(sizeof(char));
	if (c != '\0')
	{
		if (c == '"')
			*q = '"';
		else if (c == '\'')
			*q = '\'';
		else
			*q = 'a';
	}
	return (q);
}

void	more_pipes(char *s)
{
	int	i;

	i = 0;
	if (*s)
	{
		if (*(s) == '|')
			error_handling(1);
		while (*s && *s == ' ')
			s++;
		if (*s == '|')
			error_handling(1);
	}
}

int	word_count(char *s, char c)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		quote = *(quote_detection(s[i]));
		if (quote != 'a')
		{
			i++;
			while (s[i] && s[i] != quote)
				i++;
			i++;
		}
		if (quote == 'a')
		{
			if (i != 0 && s[i] != '|')
				i++;
			while (s[i] && *(quote_detection(s[i])) == 'a')
			{
				if (s[i] == c)
				{
					i++;
					count++;
					more_pipes(&s[i]);
				}
				i++;
			}
		}
	}
	return (count);
}

//char *word_allocate(char *str, char c)
//{
//	int	i;
//	char *str_malloc;
//
//
//}

//char	*word_allocate(char *str, char c)
//{
//	int			i;
//	char		*str_malloc;
//
//	i = 0;
//	while (str[i] && str[i] != c)
//		i++;
//	str_malloc = (char *)malloc(sizeof(char) * (i + 1));
//	if (!str_malloc)
//		return (NULL);
//	i = 0;
//	while (str[i] && str[i] != c)
//	{
//		str_malloc[i] = str[i];
//		i++;
//	}
//	str_malloc[i] = '\0';
//	return (str_malloc);
//}


char	**ft_split(char *str, char c)
{
	size_t	i;
	char	**arr;

	i = 0;
//	arr = (char **)malloc(sizeof(char *) * (word_count(str, c) + 1));
	if (!arr)
		return (NULL);
	while (*str)
	{
		if (*str && (*str == '"' || *str == '\''))
		{
			while (*str && (*str != '"' || *str != '\''))
				str++;
			if (*str && (*str == '"' || *str == '\''))
			{
				str++;
				if (*str && *(str) != '"' && *str != '\'' && *str == c)
				{
					while (*str && *str == c)
						str++;
					if (*str && *str != c)
					{
					//	arr[i] = word_allocate(str, c);
						if (!arr[i])
							return (NULL);
						i++;
					}
					while (*str && *str != c)
						str++;
				}
			}
		}
		str++;
	}
	arr[i] = NULL;
	return (arr);
}

#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av)
{
	(void)ac;
	int i = -1;
	char *cmd = readline("c2r8s3");
	printf("count == %d\n", word_count(cmd, '|'));
//	while (++i < 2)
//	{
//		printf("%s\n", arr[i]);
//	}
}

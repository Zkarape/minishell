/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   summerize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:13:41 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/03 22:25:56 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_substr_m(char *s, int start, int end)
{
	char *dst;
	int	i;

	i = 0;
	dst = malloc(sizeof(char) * (end - start + 1));
	while (start < end)
	{
		dst[i] = s[start];
		i++;
	}
	return (dst);
}

char	quote_detection(char c)
{
	if (c == '"')
		return (c);
	else if (c == '\'')
		return (c);
	else
		return ('a');
}

int	find_d_quote(char *s, char quote)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == quote)
			return (i);
	return (NULL);
}

int	until_d_next_quote(char quote, char *s)
{
	int	start;

	start = find_d_quote(s, quote) + 1;
	if (quote != 'a')
	{
		while (s[start] && s[start] != quote)
			start++;
	}
	return (start);
}

int	from_d_end(char quote, char *s)
{
	int	end;
	int	start2;

	start2 = until_d_next_quote(quote, s);
	end = 0;
	
}

void	group_until_pipe(char *s)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	if (s[0] == '|')
		error_handling(1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i += find_d_quote(&s[i], s[i]);
		else if (s[i] == '|')
		{
			ft_substr_m(s, start, i);
		}
		i++;
		strart = i;
	}
}

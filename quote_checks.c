/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrosy <vpetrosy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:42:59 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/21 22:08:54 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_unquoted(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] != '"')
				return (0);
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] != '\'')
				return (0);
		}
		i++;
	}
	return (1);
}

char	*strcpy_noquotes(char *str, char c)
{
	int		i;
	int		j;
	int		count;
	char	*cpy;

	i = -1;
	count = 0;
	j = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	count = ft_strlen(str) - count;
	cpy = malloc(sizeof(char) * count + 1);
	if (!cpy)
		return (NULL);
	i = -1;
	while (str[++i])
		if (str[i] != c)
			cpy[j++] = str[i];
	cpy[j] = '\0';
	return (cpy);
}

char	*adding_quotes(char *s)
{
	int		i;
	int		j;
	char	*dst;

	i = -1;
	j = 1;
	if (!s)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s) + 3));
	dst[0] = '"';
	while (s[++i])
	{
		dst[j] = s[i];
		j++;
	}
	dst[j] = '"';
	dst[++j] = '\0';
	return (dst);
}

char *removing_fst_lst_dbl_quotes(char *s)
{       
	char *dst;
	int len;
	int i;
	int j;

	len = strlen(s);
	if (len < 2) {
		return NULL; // invalid input
	}
	dst = malloc(sizeof(char) * (len - 1));
	if (dst == NULL) {
		return NULL; // memory allocation failed
	}
	i = 1;
	j = 0;
	while (i < len - 1) { // skip first and last quotes
		dst[j] = s[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return dst;
}

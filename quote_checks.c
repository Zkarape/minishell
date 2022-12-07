/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:42:59 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/07 20:50:29 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_d_unquote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if(s[i] != '"')
				return (0);
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if(s[i] != '\'')
				return (0);
		}
		i++;
	}
	return (1);
}

char	*strcpy_noquotes(char *str, char c)
{
	int		i;
	int		count;
	char	*cpy;

	i = -1;
	count = 0;
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
			cpy[i] = str[i];
	cpy[i] = '\0';
	return (cpy);
}
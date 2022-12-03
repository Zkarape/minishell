/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:42:59 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/01 18:35:36 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_d_quote(char *s)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (i < len - 1)
	{
		if (s[i] == '"')
		{
			j = i + 1;
			while (s[j] && s[j] != '"')
				j++;
			if (s[j] != '"')
				errors_for_quotes(0);
		}
		else if (s[i] == '\'')
		{
			j = i + 1;
			while (s[j] && s[j] != '\'')
				j++;
			if (s[j] != '\'')
				errors_for_quotes(0);
		}
		i++;
	}
	return (1);
}
//
//int main()
//{
//	char s[3];
//	gets(s);
//	printf("%d\n", find_d_quote(s));
//}

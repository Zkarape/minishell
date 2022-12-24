/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:59:12 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/24 20:32:36 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	find_d_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[++i])
		if (is_quote(s[i]))
			return (i - 1);
	return (i);
} 

int	find_dollar_del(char *s, int q_idx)
{
	int		i;
	int		start;
	int		k;
	char	*del;

	i = 0;
	start = 0;
	while (s[i] && i < q_idx)
	{
		k = 0;
		if (s[i] == '$')
		{
			i++;
			start = i;
			while (!ft_is_space(s[i]) && !is_quote(s[i]) && s[i] != '$')
			{
				i++;
				k++;
			}
			del = ft_substr_m(s, start , start + k);
			printf("del = %s\n", del);
			//compare del with env_vars
		}
		else
			i++;
	}
	return (i);
}

void	expand(char *s)
{
	int	i;
	
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"')
			i += find_dollar_del(&s[i], find_d_quote(&s[i], s[i]));
		else if (s[i] =='\'')
			i += find_d_quote(&s[i], s[i]);
		else
			i += find_dollar_del(&s[i], find_d_quotes(&s[i]));
	}
}

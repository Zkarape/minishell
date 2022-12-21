/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:59:12 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/21 22:36:21 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	find_dollar_with_arg(char *s_m, int q_idx, int flag)
{
	int		i;
	int		k;
	char	*del;

	i = 0;
	k = 0;
	while (s_m[i] && i < q_idx)
	{
		if (s_m[i] == '$')
		{
			while (!is_space(s_m[i]))
				k++;
			del = ft_substr_m(s_m, i, i + k);
			//compare del with env_vars
		}
	}
}

void	expand(char *s, int start, int end)
{
	int		i;
	char	*s_m;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '"')
		{
			s_m = ft_substr_m(s, i, find_d_quote(&s[i], s[i]));
		}
	}
}

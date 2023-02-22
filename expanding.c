/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:24:09 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/21 21:56:57 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_del(char *s, t_args *a)
{
	int		k;
	char	*del;

	k = 0;
	del = NULL;
	while (!ft_is_space(s[a->i]) && !is_quote(s[a->i])
		&& s[a->i] && s[a->i++] != '$')
		k++;
	if (s[a->i - 1] == '$' && is_quote(s[a->i]))
		return (del);
	else
		del = ft_substr_m(s, a->exp_start, a->exp_start + k);
	return (del);
}

char	*find_start_end_for_expand(t_args *a, char *s)
{
	char	*del;
	char	*get;
	char	*str;

	del = NULL;
	get = NULL;
	str = NULL;
	a->end = a->i;
	a->i++;
	a->exp_start = a->i;
	del = find_del(s, a);
	if (del && !(*del)) // for one $
		a->end++;
	str = ft_strjoin2(str, s, a->end, a->start);
	a->start = a->end + ft_strlen(del) + 1;
	if (del && !(*del)) //for one $
		(a->start)--;
	if (a->hdoc_flg)
		get = get_env(a->env_lst, del);
	else
		get = get_exp(a->exp_lst, del);
	str = ft_strjoin2(str, get, ft_strlen(get), 0);
	if (del)
		free(del);
	return (str);
}

//end is always on '$', start is 0, then it becomes the next of del
char	*find_dollar_del(char *s, t_args *a)
{
	char	*str;

	str = NULL;
	while (s[a->i] && a->i < a->q_idx)
	{
		if ((s[a->i] == '$' && s[a->i + 1] && a->i + 1 < a->q_idx)
			|| (s[a->i] == '$' && a->i + 1 == a->q_idx && !a->hdoc_flg))
		{
			str = find_start_end_for_expand(a, s);
		}
		else
			a->i++;
	}
	if (s[a->i] == '\'' && !a->hdoc_flg) // for $'$HOME'
		a->i--;
	return (str);
}

char	*expand(char *s, t_args *args)
{
	char	*str;

	args->i = 0;
	str = NULL;
	args->start = 0;
	args->hdoc_flg = 0;
	while (s && *s && s[args->i])
	{
		if (s[args->i] == '"')
		{
			args->q_idx = find_d_quote2(s, s[args->i], args->i);
			str = find_dollar_del(s, args);
		}
		else if (s[args->i] == '\'')
			args->i = find_d_quote2(s, s[args->i], args->i);
		else
		{
			args->q_idx = find_d_quotes(s, args->i);
			str = find_dollar_del(s, args);
		}
		if (s[args->i])
			args->i++;
	}
	str = ft_strjoin2(str, s, args->i, args->start);
	return (str);
}

char	*hdoc_expand(char *s, t_args *args)
{
	char	*str;

	str = NULL;
	args->i = -1;
	args->start = 0;
	args->hdoc_flg = 1;
	while (s[++args->i])
	{
		args->q_idx = find_d_quotes(s, args->i);
		str = find_dollar_del(s, args);
	}
	str = ft_strjoin2(str, s, args->i, args->start);
	return (str);
}

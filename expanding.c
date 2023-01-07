/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:59:12 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/07 20:03:13 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	find_d_quote2(char *s, char quote, int i)
{
	while (s[++i])
		if (s[i] == quote)
			return (i);
	return (0);
}

int	find_d_quotes(char *s, int i)
{
	while (s[i])
	{
		if (is_quote(s[i + 1]) || !s[i + 1])
			return (i);
		i++;
	}
	return (0);
}

char	*get_env(t_env_lst *env_lst, char *del)
{
	t_env	*env_node;

	env_node = env_lst->head->next;
	while (env_node->next && del)
	{
		if (!ft_strncmp(env_node->data, del, ft_strlen(del)))
			return (env_node->data + ft_strlen(del) + 1);
		env_node = env_node->next;
	}
	return (NULL);
}

int	find_del(char *s, char **del, int i, int start, t_env_lst *env_lst)
{
	int	k;

	k = 0;
	while (!ft_is_space(s[i]) && !is_quote(s[i]) && s[i])
	{
		if (s[i] == '$')
		{
			*del = NULL;
			printf("del == %s\n", *del);
			return (i);
		}
		i++;
		k++;
	}
	*del = ft_substr_m(s, start, start + k);
	printf("del == %s\n", *del);
	return (i);
}

int	find_dollar_del(char *s, char **str, int i, int q_idx, int *start, t_env_lst *env_lst)
{
	int		j;
	int		exp_start;
	char	*del;
	int		end;

	end = 0;
	j = 0;
	exp_start = 0;	
	while (s[i] && i < q_idx)
	{
		if ((s[i] == '$' && s[i + 1] && i + 1 < q_idx) 
			|| (s[i + 1] == '$' && i + 1 == q_idx))
		{
			end = i;
			i++;
			exp_start = i;
			i = find_del(s, &del, i, exp_start, env_lst);
			if (!del)
				end++;
			printf("start == %d, end == %d, s[end] == %c\n", *start, end, s[end]);
			*str = ft_strjoin(*str, s, end, *start);
			*start = end + ft_strlen(del) + 1;
			printf("start == %d, end == %d\n", *start, end);
			*str = ft_strjoin(*str, get_env(env_lst, del), ft_strlen(get_env(env_lst, del)), 0);
			printf("str == %s, i == %d\n", *str ,i);
		}
		else
		{
			i++;
		}
	}
	printf("str == %s\n", *str);
	return (i);
}

void	expand(char *s, t_cmd *cmd_node, t_env_lst *env_lst)
{
	int		i;
	int		start;
	char	*str;
	
	i = -1;
	str = NULL;
	start = 0;
	while (s[++i])
	{
		if (s[i] == '"')
		{
			i = find_dollar_del(s, &str, i, find_d_quote2(s, s[i], i), &start, env_lst);
		}
		else if (s[i] == '\'')
		{
			i = find_d_quote2(s, s[i], i);
		}
		else
		{
			printf("s[i] == %c\n", s[i]);
			i = find_dollar_del(s, &str, i, find_d_quotes(s, i), &start, env_lst);
		}
	}
	str = ft_strjoin(str, s, i, start);
	printf("%s\n", str);
}

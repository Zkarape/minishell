/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:59:12 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/27 22:25:24 by zkarapet         ###   ########.fr       */
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

int	if_is_dollar(char *s, char **del, int i, int start, t_env_lst *env_lst)
{
	int		k;

	k = 0;
	while (!ft_is_space(s[i]) && !is_quote(s[i]) && s[i])
	{
		i++;
		k++;
	}
	*del = ft_substr_m(s, start, start + k);
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
		if (s[i] == '$' && s[i + 1] && i + 1 < q_idx)
		{
			end = i;
			i++;
			exp_start = i;
			i = if_is_dollar(s, &del, i, exp_start, env_lst);
			*str = ft_strjoin(*str, s, end, *start);
			*start = end + ft_strlen(del) + 1;
			*str = ft_strjoin(*str, get_env(env_lst, del), ft_strlen(get_env(env_lst, del)), 0);
		}
		else
			i++;
	}
	//if (!i)
	//	printf("mtaa %s\n", get_env(env_lst, NULL));
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
			i = find_dollar_del(&s[i], &str, i, find_d_quotes(s, i), &start, env_lst);
		}
	}
	str = ft_strjoin(str, s, i, start);
	printf("%s\n", str);
}

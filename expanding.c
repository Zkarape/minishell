/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:59:12 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/26 14:02:28 by zkarapet         ###   ########.fr       */
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
		{
		//	printf("******************** %s\n", env_node->data + ft_strlen(del) + 1);
			return (env_node->data + ft_strlen(del) + 1);
		}
		env_node = env_node->next;
	}
	return (NULL);
}

int	if_is_dollar(char *s, char **del, int i, int start, t_env_lst *env_lst)
{
	int		k;

	k = 0;
	while (!ft_is_space(s[i]) && !is_quote(s[i]) && s[i] != '$' && s[i])
	{
		i++;
		k++;
	}
	*del = ft_substr_m(s, start, start + k);
	printf("del == %s\n", *del);
//	printf("mtaa1 %s\n", get_env(env_lst, *del));
	return (i);
}

int	find_dollar_del(char *s, int q_idx, t_env_lst *env_lst, t_cmd *cmd_node)
{
	int		i;
	int		start;
	char	*del;

	i = 0;
	start = 0;
	while (s[i] && i < q_idx)
	{

		if (s[i] == '$')
		{
			i++;
			start = i;
			i = if_is_dollar(s, &del, i, start, env_lst);
	//		printf("s[START] == %c\n", s[start - 1]);
			printf("%s\n", str_return_trimmed(s, start - 1, i, get_env(env_lst, del)));
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
	int	i;
	
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"')
		{
			i += find_dollar_del(&s[i], find_d_quote(&s[i], s[i]), env_lst, cmd_node);
		}
		else if (s[i] =='\'')
			i += find_d_quote(&s[i], s[i]);
		else
		{
			i += find_dollar_del(&s[i], find_d_quotes(&s[i]), env_lst, cmd_node);
		}
	}
}

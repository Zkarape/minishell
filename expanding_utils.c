/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:53:08 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/21 21:58:20 by zkarapet         ###   ########.fr       */
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
		{
			if (s[i] == '$')
				return (i + 1);
			return (i + 1);
		}
		i++;
	}
	return (0);
}

char	*get_exp(t_env_lst *exp_lst, char *del)
{
	t_env	*exp_node;
	int		k;

	exp_node = exp_lst->head->next;
	while (exp_node->next && del && *del)
	{
		k = until_equal_sign(&exp_node->data[11]);
		if (!ft_strncmp(&exp_node->data[11], del, k) && k == ft_strlen(del))
			return (ft_strdup(removing_fst_lst_dbl_quotes(exp_node->data
						+ 11 + ft_strlen(del) + 1)));
		exp_node = exp_node->next;
	}
	return (NULL);
}

char	*get_env(t_env_lst *env_lst, char *del)
{
	t_env	*env_node;

	env_node = env_lst->head->next;
	while (env_node->next && del && *del)
	{
		if (!ft_strncmp(env_node->data, del, ft_strlen(del)))
			return (env_node->data + ft_strlen(del) + 1);
		env_node = env_node->next;
	}
	return (NULL);
}

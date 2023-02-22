/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:37:14 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/21 22:08:37 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(t_env *a, t_env *b)
{
	char	*temp;

	temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void	sort(t_env_lst *exp_lst)
{
	t_env	*cur;
	t_env	*ind;

	cur = exp_lst->head->next;
	ind = NULL;
	if (!exp_lst->head->next)
		return ;
	while (cur->next)
	{
		ind = cur->next;
		while (ind->next)
		{
			if (ft_strcmp(cur->data, ind->data) > 0)
				swap(cur, ind);
			ind = ind->next;
		}
		cur = cur->next;
	}
}

char	*equality_out_of_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (is_quote(s[i]))
			i += find_last_quote(&s[i], s[i]);
		else if (s[i] == '=')
		{
			if (error_checks_for_var(s, i, 1))
				return (NULL);
			return (&s[i + 1]);
		}
	}
	return (NULL);
}

t_env	*is_in_env_or_not(t_env_lst *env_lst, char *arg)
{
	t_env	*cur;
	int		k;

	cur = env_lst->head->next;
	while (cur->next)
	{
		k = until_equal_sign(cur->data);
		if (!ft_strncmp(cur->data, arg, k + 1))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_env	*is_in_exp_or_not(t_env_lst *exp_lst, char *arg)
{
	t_env	*cur;
	int		k;

	cur = exp_lst->head->next;
	while (cur->next)
	{
		k = until_equal_sign(&cur->data[11]);
		if (!ft_strncmp(&cur->data[11], arg, k + 1))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

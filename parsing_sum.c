/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:54:15 by zkarapet          #+#    #+#             */
/*   Updated: 2023/03/04 00:59:30 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	cmd_expanded(t_cmd_lst *cmd_lst, t_args *args)
{
	t_cmd	*cur;
	char	*str;

	cur = cmd_lst->head;
	str = NULL;
	while (cur)
	{
		str = expand(cur->args, args);
		free(cur->args);
		cur->args = str;
		cur = cur->next;
	}
}

char	**no_cmd_clear(char **arr)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	while (arr[++i])
	{
		str = filling_with_nulls(arr[i]);
		free(arr[i]);
		arr[i] = str;
	}
	arr[i] = NULL;
	return (arr);
}

void	update_status(t_args *a)
{
	t_env	*cur;
	char	*itoa;
	char	*joined;
	char	*duped;

	itoa = NULL;
	joined = NULL;
	cur = a->exp_lst->head->next;
	while (cur->next)
	{
		if (cur->data[11] == '?')
		{
			remove_from_between(cur, a->exp_lst);
			break ;
		}
		cur = cur->next;
	}
	itoa = ft_itoa(g_status);
	duped = ft_strdup("declare -x ?=\"");
	joined = ft_strjoin3(duped, itoa, "\"");
	env_lst_add_last(a->exp_lst, joined);
	free(joined);
	free(duped);
	free(itoa);
}

void	cmd_quote_clear(t_cmd_lst *cmd_lst)
{
	t_cmd	*cur;
	char	**arr;

	cur = cmd_lst->head;
	arr = NULL;
	while (cur)
	{
		arr = split(cur->args, ' ');
		if (!arr)
			exit(1);
		cur->no_cmd = no_cmd_clear(arr);
		cur = cur->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:41:39 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/22 19:23:43 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_a(t_args *a, int f)
{
	dbl_free(a->env);
	if (!f)
		pipefds_free(a->pipefds);
//	free(a->file);
	free(a->pids);
	a->env = NULL;
//	a->file = NULL;
	a->pids = NULL;
}

void	pipefds_free(pid_t (*pipefds)[2])
{
	free(pipefds);
	pipefds = NULL;
}

void	dbl_free(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	free(arr);
	arr = NULL;
}

void	env_def_free(t_env *node)
{
	free(node);
	node = NULL;
}

void	env_lst_destruct(t_env_lst **list)
{
	t_env	*cur;
	t_env	*tmp;

	tmp = NULL;
	if (list && *list)
	{
		cur = (*list)->head->next;
		while (cur)
		{
			tmp = cur->next;
			env_def_free(cur);
			cur = tmp;
		}
	}
	free(list);
	list = NULL;
}

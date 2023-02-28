/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:17:18 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/28 19:55:38 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_lst_destruct(t_cmd_lst **list, t_cmd *until)
{
	t_cmd	*cur;
	t_cmd	*tmp;

	tmp = NULL;
	if (list && *list)
		cur = (*list)->head;
	else
		cur = NULL;
	while (cur != until)
	{
		tmp = cur->next;
		cmd_def_free(cur);
		cur = tmp;
	}
	free(until);
	free(*list);
	*list = NULL;
}

void	update_free(t_cmd_lst **cmd_lst, t_list **lst, char *s, t_args *a)
{
	update_status(a);
	free_a(a);
	free(s);
	lst_destruct(lst);
	cmd_lst_destruct(cmd_lst, NULL);
}

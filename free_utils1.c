/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:16:21 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/22 19:05:47 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_def_free(t_node *node)
{
	if (node)
	{
		free(node->data);
		free(node);
	}
}

void	lst_destruct(t_list **list)
{
	t_node	*cur;
	t_node	*tmp;

	tmp = NULL;
	if (list && *list)
		cur = (*list)->head;
	else
		cur = NULL;
	while (cur)
	{
		tmp = cur->next;
		node_def_free(cur);
		cur = tmp;
	}
	free(*list);
	*list = NULL;
}

void	red_def_free(t_red *node)
{
	if (node)
	{
		free(node->file);
		free(node);
	}
}

void	red_lst_destruct(t_red_lst **list)
{
	t_red	*cur;
	t_red	*tmp;

	tmp = NULL;
	cur = NULL;
	if (list && *list)
		cur = (*list)->head;
	while (cur)
	{
		tmp = cur->next;
		red_def_free(cur);
		cur = tmp;
	}
	free(*list);
	*list = NULL;
}

void	cmd_def_free(t_cmd *node)
{
	if (node)
	{
		free(node->args);
		red_lst_destruct(&node->red_lst);
		dbl_free(node->no_cmd);
		free(node);
	}
}

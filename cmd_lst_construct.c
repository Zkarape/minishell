/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_construct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:46:18 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/19 17:30:01 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_lst_print(t_cmd_lst *list)
{
	t_cmd	*cur;

	cur = list->head;
	while (cur)
	{
		printf("%s-> ", cur->args);
		cur = cur->next;
	}
	printf("NULL\n");
}

t_cmd_lst	*cmd_lst_construct(void)
{
	t_cmd_lst	*new_list;

	new_list = malloc(sizeof(t_cmd_lst));
	if (!new_list)
		exit(1);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

void	cmd_lst_add_last(t_cmd_lst *list)
{
	t_cmd	*new_node;

	new_node = cmd_node_initialize();
	if (list->size == 0)
	{
		list->head = new_node;
		list->tail = list->head;
	}
	else
		list->tail->next = new_node;
	list->tail = new_node;
	list->size++;
}

t_cmd	*cmd_node_initialize(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->fd_out = 1;
	node->fd_in = 0;
	node->hdoc_fd = -1;
	node->next = NULL;
	node->red_lst = NULL;
	node->no_cmd = NULL;
	return (node);
}

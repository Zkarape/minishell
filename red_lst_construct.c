/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_lst_construct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:56:51 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/22 18:58:20 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_lst_print(t_red_lst *list)
{
	t_red	*cur;

	cur = list->head;
	while (cur)
	{
		printf("%s %d-> ", cur->file, cur->type);
		cur = cur->next;
	}
	printf("NULL\n");
}

t_red_lst	*red_lst_construct(void)
{
	t_red_lst	*new_list;

	new_list = malloc(sizeof(t_red_lst));
	if (!new_list)
		return (NULL);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	new_list->heredoc_k = 0;
	return (new_list);
}

t_red	*red_node_initialize_pro(char *file, int type)
{
	t_red	*node;

	node = malloc(sizeof(t_red));
	if (!node)
		return (NULL);
	node->type = type;
	node->file = file;
	printf("file  == %s\n", node->file);
	node->next = NULL;
	return (node);
}

void	red_add(t_red_lst *list, char *file, int type)
{
	t_red	*new_node;

	new_node = red_node_initialize_pro(file, type);
	if (list->size == 0)
	{
		list->head = new_node;
		list->tail = list->head;
	}
	else
		list->tail->next = new_node;
	list->tail = new_node;
	if (type == 2)
	{
		list->heredoc_k++;
	}
	list->size++;
}

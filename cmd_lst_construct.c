/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_construct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrosy <vpetrosy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:03:26 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/07 20:24:58 by vpetrosy         ###   ########.fr       */
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
		return (NULL);
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
	node->next = NULL;
	node->red_lst = NULL;
	return (node);
}

void	more_reds(char *s, char c)
{
	int	i;

	i = 0;
	if (*s)
	{
		if (*(s) == c )
			ft_print_error_and_exit("parse error near '<'\n", EXIT_FAILURE);
		while (*s && *s == ' ')
			s++;
		if (*s == c)
			ft_print_error_and_exit("parse error near '<'\n", EXIT_FAILURE);
	}
}

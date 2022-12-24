/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:06:39 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/24 21:55:24 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lst_print(t_env_lst *list)
{
	t_env	*cur;

	cur = list->head;
	while (cur)
	{
		printf("%s-> ", cur->data);
		cur = cur->next;
	}
}

t_env	*env_def_initialize()
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->data = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env_lst	*env_lst_construct(void)
{
	t_env_lst	*new_list;

	new_list = malloc(sizeof(t_env_lst));
	if (!new_list)
		return (NULL);
	new_list->head = env_def_initialize();
	new_list->tail = env_def_initialize();
	new_list->head->next = new_list->tail;
	new_list->tail->prev = new_list->head;
	new_list->size = 0;
	return (new_list);
}

t_env	*env_initialize(char *data, t_env *next, t_env *prev)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = next;
	node->prev = prev;
	return (node);
}

void	add_between(t_env *predecessor, t_env *successor, char *data)
{
	t_env	*env_node;

	env_node = env_initialize(data, successor, predecessor);
	predecessor->next = env_node;
	successor->prev = env_node;
}

void	env_lst_add_last(t_env_lst *list, char *data)
{
	add_between(list->tail->prev, list->tail, data);
	list->size++;
}

void	remove_from_between(t_env *env, t_env_lst *env_lst)
{
	env->prev->next = env->next;
	env->next->prev = env->prev;
	env_lst->size--;
	free(env);
}

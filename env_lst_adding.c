/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_adding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:24:08 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/19 20:57:04 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (env && env_lst)
	{
		env->prev->next = env->next;
		env->next->prev = env->prev;
		env_lst->size--;
		free(env->data);
		free(env);
	}
}

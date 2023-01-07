/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:06:21 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/07 16:39:19 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*getting_env(char **env)
{
	t_env_lst	*env_lst;
	int			i;

	env_lst = env_lst_construct();
	i = -1;
	while (env[++i])
		env_lst_add_last(env_lst, env[i]);
//	env_lst_print(env_lst);
	return (env_lst);
}

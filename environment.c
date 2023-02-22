/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 22:06:21 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/19 13:13:00 by zkarapet         ###   ########.fr       */
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
	return (env_lst);
}

char	*get_environment(char *name, char **g_envp)
{
	int	i;

	i = 0;
	while (g_envp[i])
	{
		if (!ft_strncmp(g_envp[i], name, ft_strlen(name)))
			return (g_envp[i] + ft_strlen(name));
		i++;
	}
	return (NULL);
}

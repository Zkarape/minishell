/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:56:46 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/22 17:43:00 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build(t_cmd *cmd, t_args *a)
{
	int	i;

	i = 1;
	if (i)
	{
		if (cmd->no_cmd[0] && !ft_strncmp(cmd->no_cmd[0], "exit", 5))
			g_status = ft_exit(cmd);
		else if (!ft_strncmp(ft_str_tolower(&cmd->no_cmd[0]), "env", 4))
			g_status = env(a->env_lst, cmd->no_cmd[1], a->env);
		else if (!ft_strncmp(ft_str_tolower(&cmd->no_cmd[0]), "pwd", 4))
			g_status = pwd();
		else if (!ft_strncmp(cmd->no_cmd[0], "cd", 3))
			g_status = cd(cmd->no_cmd[1], a->env, a);
		else if (!ft_strncmp(ft_str_tolower(&cmd->no_cmd[0]), "echo", 5))
			g_status = echo(cmd);
		else if (!ft_strncmp(cmd->no_cmd[0], "unset", 6))
			g_status = unset(a->env_lst, a->exp_lst, cmd);
		else if (!ft_strncmp(cmd->no_cmd[0], "export", 7))
			g_status = ft_export(cmd, a);
		else
			i = 0;
	}
	return (i);
}

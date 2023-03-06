/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:56:46 by zkarapet          #+#    #+#             */
/*   Updated: 2023/03/03 22:16:40 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd, t_args *a)
{
	if (a->size + 1 != 1)
		return (0);
	if (!ft_strncmp(cmd->no_cmd[0], "exit", 5))
		return (1);
	else if (!ft_strncmp(ft_str_tolower(&cmd->no_cmd[0]), "env", 4))
		return (1);
	else if (!ft_strncmp(ft_str_tolower(&cmd->no_cmd[0]), "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd->no_cmd[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(ft_str_tolower(&cmd->no_cmd[0]), "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd->no_cmd[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd->no_cmd[0], "export", 7))
		return (1);
	return (0);
}

void	closes_one_builtin(t_cmd *cmd, int d, int *in_, int *out_)
{
	if (d)
	{
		dup2(*in_, STDIN_FILENO);
		dup2(*out_, STDOUT_FILENO);
		close(*in_);
		close(*out_);
		close_in_out(cmd->fd_in);
		close_in_out(cmd->fd_out);
	}
}

void	dup_for_one_builtin(t_cmd *cmd, int d, int *in_, int *out_)
{
	if (d)
	{
		*in_ = dup(STDIN_FILENO);
		*out_ = dup(STDOUT_FILENO);
		dup2(cmd->fd_in, 0);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
}

int	build(t_cmd *cmd, t_args *a)
{
	int	i;
	int	in_;
	int	out_;

	i = 1;
	dup_for_one_builtin(cmd, is_builtin(cmd, a), &in_, &out_);
	if (!ft_strncmp(cmd->no_cmd[0], "exit", 5))
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
	closes_one_builtin(cmd, is_builtin(cmd, a), &in_, &out_);
	return (i);
}

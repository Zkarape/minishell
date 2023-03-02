/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:06:24 by zkarapet          #+#    #+#             */
/*   Updated: 2023/03/02 16:36:25 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_checks(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[0] == '-')
	{
		i++;
		if (s[i] && s[i] != 'n')
			return (0);
	}
	return (1);
}

int	echo(t_cmd *cmd_node)
{
	int	i;
	int	k;

	i = 1;
	k = 1;
	if (!cmd_node->no_cmd[1])
		return (0);
	if (echo_checks(cmd_node->no_cmd[1]))
	{
		i++;
		k = 0;
	}
	while (cmd_node->no_cmd[i])
	{
		ft_putstr_fd(cmd_node->no_cmd[i], 1, 0);
		i++;
		if (cmd_node->no_cmd[i])
			ft_putstr_fd(" ", 1, 0);
	}
	if (k)
		ft_putstr_fd("\n", 1, 0);
	return (0);
}

void	remove_cur_env_node(t_env_lst *env_lst, char *s)
{
	t_env	*cur;

	cur = env_lst->head->next;
	while (cur->next)
	{
		if (!ft_strncmp(cur->data, s, until_equal_sign(cur->data) + 1))
		{
			remove_from_between(cur, env_lst);
			break ;
		}
		cur = cur->next;
	}
}

int	unset(t_env_lst *env_lst, t_env_lst *exp_lst, t_cmd *cmd)
{
	int		i;
	int		q;
	t_env	*cur;

	i = 0;
	q = 0;
	while (cmd->no_cmd[++i])
	{
		cur = exp_lst->head->next;
		if (error_checks_for_var(cmd->no_cmd[i], ft_strlen(cmd->no_cmd[i]), 1))
			q++;
		while (cur->next)
		{
			if (!cmpfree(before(&cur->data[11]), cmd->no_cmd[i], 0))
			{
				remove_cur_env_node(env_lst, &cur->data[11]);
				remove_from_between(cur, exp_lst);
				break ;
			}
			cur = cur->next;
		}
	}
	if (q == i - 1)
		return (1);
	return (0);
}

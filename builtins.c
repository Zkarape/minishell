/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:06:24 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/21 21:26:57 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	until_equal_sign(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '=')
		i++;
	return (i);
}

int	echo(t_cmd *cmd_node)
{
	int	i;
	int	k;

	i = 1;
	k = 1;
	if (!cmd_node->no_cmd[1])
		return (0);
	if (ft_strcmp(cmd_node->no_cmd[1], "-n") == 0)
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

int	unset(t_env_lst *env_lst, t_env_lst *exp_lst, t_cmd *cmd_node)
{
	int		i;
	int		k;
	t_env	*exp_node;

	i = 0;
	exp_node = exp_lst->head->next;
	while (cmd_node->no_cmd[++i])
	{
		if (error_checks_for_var(cmd_node->no_cmd[i],
				ft_strlen(cmd_node->no_cmd[i]), 1))
			return (1);
		while (exp_node->next)
		{
			k = until_equal_sign(&exp_node->data[11]);
			if (!ft_strncmp(&exp_node->data[11], cmd_node->no_cmd[i], k)
				&& k == ft_strlen(cmd_node->no_cmd[i]))
			{
				remove_cur_env_node(env_lst, &exp_node->data[11]);
				remove_from_between(exp_node, exp_lst);
				break ;
			}
			exp_node = exp_node->next;
		}
	}
	return (0);
}

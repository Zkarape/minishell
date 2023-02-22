/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:51:16 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/21 21:56:21 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nothing_but_int(char *str)
{
	int	i;

	i = -1;
	if (!str || !*str)
		return (0);
	while (str[++i] && (str[i] >= '0' && str[i] <= '9'))
		;
	if (str[0] == '-' || str[0] == '+')
		while (str[++i] && (str[i] >= '0' && str[i] <= '9'))
			;
	if (!str[i])
		return (1);
	return (0);
}

long long	ft_atoi(const char *str)
{
	long long	res;
	int			min;
	int			i;

	min = 1;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ' || str[i] == 0)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * min);
}

int	check_long_long(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len >= 20)
		return (1);
	if (len == 19 && ft_strcmp(s, "9223372036854775807") > 0)
		return (1);
	if (len == 20 && ft_strcmp(s, "-9223372036854775808") > 0)
		return (1);
	return (0);
}

void	put_status_and_exit(int status)
{
	g_status = status;
	exit(status);
}

int	ft_exit(t_cmd *cmd_head)
{
	long long	x;
	int			i;

	i = -1;
	if (!nothing_but_int(cmd_head->no_cmd[1])
		|| check_long_long(cmd_head->no_cmd[1]))
	{
		ft_putstr("exit\nexit: numeric argument required\n");
		put_status_and_exit(255);
	}
	while (cmd_head->no_cmd[++i])
		;
	if (i > 2)
	{
		ft_putstr("exit\nexit: too many arguments\n");
		return (1);
	}
	if (cmd_head->no_cmd[1])
	{
		x = ft_atoi(cmd_head->no_cmd[1]);
		put_status_and_exit(x % 256);
	}
	put_status_and_exit(0);
	return (0);
}

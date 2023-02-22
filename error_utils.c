/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:30:41 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/21 21:52:43 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
}

int	pipe_error(int pip)
{
	if (pip < 0)
	{
		perror("pipe() returns -1\n");
		return (1);
	}
	return (0);
}

void	ft_print_error_and_exit(char *error, int code)
{
	ft_putstr(error);
	g_status = code;
	exit(code);
}

void	dup_error(int du)
{
	if (du < 0)
		ft_print_error_and_exit("dup2 is < 0", 1);
}

void	ft_print_error_with_arg(char *cmd, char *arg)
{
	char	*msg;
	char	*s1;
	char	*s2;

	s1 = ft_strjoin_m(cmd, ": ");
	s2 = ft_strjoin_m(arg, ": ");
	msg = ft_strjoin3(s1, s2, "No such file or directory\n");
	ft_putstr(msg);
}

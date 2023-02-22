/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:29:46 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/23 00:32:09 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	hdoc_pipe_check(int fd[2], t_cmd *cmd)
{
	if (pipe_error(pipe(fd)))
	{
		closing_hdoc(fd, cmd, 0);
		return (1);
	}
	return (0);
}

void	close_pipefds(int (*pipefds)[2], int i, t_cmd *cur, int cl_cur)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		close(pipefds[j][0]);
		close(pipefds[j][1]);
	}
	if (cl_cur)
		closing(cur);
}

int	last_pipe_check(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0 && ft_is_space(s[i]))
		i--;
	if (i >= 0 && s[i] == '|')
		return (0);
	return (1);
}

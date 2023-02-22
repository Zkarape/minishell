/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:42:34 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/22 20:00:22 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\f'
		|| c == '\n' || c == '\r' || c == '\v');
}

void	ft_putstr_fd(char *s, int fd, int fl)
{
	write(fd, s, ft_strlen(s));
	if (fl)
		write(fd, "\n", 1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
		;
	return (i);
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

void	closing(t_cmd *cur)
{	
	while (cur)
	{
		close_in_out(cur->fd_out);
		close_in_out(cur->fd_in);
		close_in_out(cur->hdoc_fd);
		cur = cur->next;
	}
}

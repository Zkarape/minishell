/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sum_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:03:48 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/20 14:07:45 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_input_work(t_red_lst *red_lst)
{
	t_red	*cur;
	int		i;

	i = 0;
	cur = red_lst->head;
	while (cur)
	{
		if (cur->type == HEREDOC)
			i = 1;
		else if (cur->type == INPUT_REDIRECTION)
			i = 0;
		cur = cur->next;
	}
	return (i);
}

void	dup_in_or_not_ttq(t_cmd *cur, int pipe_fd_in)
{
	if (cur->fd_in == 0)
	{
		if (cur->hdoc_fd > 0)
			pipe_fd_in = cur->hdoc_fd;
		if (dup2(pipe_fd_in, STDIN_FILENO) < 0)
			ft_print_error_and_exit("dup2 failed in fd_in\n", 1);
	}
	else
	{
		if (dup2(cur->fd_in, STDIN_FILENO) < 0)
			ft_print_error_and_exit("dup2 failed in fd_in\n", 1);
	}
}

void	dup_out_or_not_ttq(t_cmd *cur, int pipe_fd_out)
{
	if (cur->fd_out == 1)
	{
		if (dup2(pipe_fd_out, STDOUT_FILENO) < 0)
			ft_print_error_and_exit("dup2 failed in fd_out\n", 1);
	}
	else
	{
		if (dup2(cur->fd_out, STDOUT_FILENO) < 0)
			ft_print_error_and_exit("dup2 failed in fd_out\n", 1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2023/03/03 22:36:47 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	

void	heredoc_utils(t_cmd *cmd, t_args *a, char **s)
{
	char	*tmp;

	tmp = NULL;
	if (find_d_quotes(a->file, 0) == ft_strlen(a->file) - 1)
	{
		tmp = hdoc_expand(*s, a);
		free(*s);
		*s = tmp;
	}
	if (cmd->yep && a->hdoc_size == 0)
	{
		ft_putstr_fd(*s, a->fd[1], 1);
		cmd->hdoc_fd = a->fd[0];
	}
	free(tmp);
	*s = NULL;
}

int	status_check(char *cleaned_file, char *s)
{
	if (g_status == -42)
	{
		g_status = 1;
		free(cleaned_file);
		free(s);
		return (1);
	}
	return (0);
}

int	heredoc(t_cmd *cmd, t_args *a)
{
	char	*s;
	char	*cleaned_file;

	s = NULL;
	cleaned_file = filling_with_nulls(a->file);
	while (1)
	{
		sig_control(2);
		s = readline("> ");
		if (!s)
			break ;
		if (status_check(cleaned_file, s))
			return (1);
		if (!(ft_strncmp(cleaned_file, s, cmp_len(cleaned_file, s)) || !s[0]))
			break ;
		heredoc_utils(cmd, a, &s);
		free(s);
	}
	if (cmd->hdoc_fd == -1 && cmd->yep && a->hdoc_size == 0)
		cmd->hdoc_fd = a->fd[0];
	free(cleaned_file);
	free(s);
	return (0);
}

void	closing_hdoc(int fd[2], t_cmd *cmd, int flag)
{
	if (flag == 0)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (flag == 1)
	{
		close(fd[1]);
		if (cmd->hdoc_fd == -1 && cmd->red_lst->heredoc_k == 0)
			close(fd[0]);
	}
}

int	big_loop(t_cmd *cmd, t_args *a)
{
	t_red	*cur;
	int		fd[2];
	int		k;

	k = 0;
	cur = cmd->red_lst->head;
	while (cur)
	{
		if (cur->type == HEREDOC)
		{
			if (hdoc_pipe_check(fd, cmd))
				return (1);
			cmd->red_lst->heredoc_k--;
			a->hdoc_size = cmd->red_lst->heredoc_k;
			a->fd = fd;
			a->file = cur->file;
			if (heredoc(cmd, a))
				k = 1;
			closing_hdoc(fd, cmd, 1);
		}
		if (k)
			return (1);
		cur = cur->next;
	}
	return (0);
}

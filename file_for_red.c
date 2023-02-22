/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_for_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:17:00 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/22 18:51:31 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red(char c)
{
	return (c == '<' || c == '>');
}

char	*file_trim(char *s, int k, int type)
{
	int		i;
	char	*file;
	char	*file_trimmed;

	i = 0;
	file_trimmed = NULL;
	file = NULL;
	if (k < 0)
		return (NULL);
	file = malloc(sizeof(char) * (k + 1));
	if (!file)
		return (NULL);
	while (s[i] && i < k)
	{
		file[i] = s[i];
		i++;
	}
	file[i] = '\0';
	file_trimmed = file;
	if (type != 2)
	{
		file_trimmed = filling_with_nulls(file);
		free(file);
		file = file_trimmed;
	}
	return (file);
}

void	close_in_out(int fd)
{
	if ((fd != 1 && fd != 0) && fd > 0)
		close(fd);
}

int	func_for_reds(t_cmd *cmd_node, t_red *red_node)
{
	if (red_node->type == INPUT_REDIRECTION)
	{
		close_in_out(cmd_node->fd_in);
		cmd_node->fd_in = open(red_node->file, O_RDONLY);
	}
	else if (red_node->type == HEREDOC && cmd_node->yep)
	{
		close_in_out(cmd_node->fd_in);
	}
	else if (red_node->type == APPEND_REDIRECTION)
	{
		close_in_out(cmd_node->fd_out);
		cmd_node->fd_out = open(red_node->file, O_WRONLY
				| O_APPEND | O_CREAT, 0644);
	}
	else if (red_node->type == OUTPUT_REDIRECTION)
	{
		close_in_out(cmd_node->fd_out);
		cmd_node->fd_out = open(red_node->file, O_WRONLY
				| O_TRUNC | O_CREAT, 0644);
	}
	if (cmd_node->fd_in == -1 || cmd_node->fd_out == -1)
		return (1);
	return (0);
}

int	red_big_loop(t_cmd *cmd)
{
	t_red	*cur;

	cur = cmd->red_lst->head;
	while (cur)
	{
		if (func_for_reds(cmd, cur))
			return (1);
		cur = cur->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:13:04 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/17 22:24:53 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red(char c)
{
	return (c == '<' || c == '>');
}

char	*less_red(char *s)
{
	char	*file;
	int		i;
	int		k;
	int		j;

	i = -1;
	k = -1;
	j = 0;
	while (s[++i])
		if (!ft_is_space(s[i]) && !is_red(s[i]))
			k++;
	file = malloc(sizeof(char) * k + 1);
	i = -1;
	while (++i < k)
		if (!ft_is_space(s[i]) && !is_red(s[i]))
			file[j++] = s[i];
	file[j] = '\0';
	return (file);
}

void	func_for_reds(char *s, t_cmd *cmd_node, int start, int end)
{
	int	i;

	i = start;
	while (s[i] && i < end)
	{
		if (s[i] == '<')
		{
			if (cmd_node->fd_out != 1)
				close(cmd_node->fd_out);
		//	if (s[i + 1] == '<')
			//heredoc	cmd_node->fd_out = open(less_red(&s[i + 2], O_RDONLY, );
			else
				cmd_node->fd_out = open(less_red(&s[i + 1]), O_RDONLY);
		}
		else if (s[i] == '>')
		{
			if (cmd_node->fd_in != 1)
				close(cmd_node->fd_in);
			if (s[i + 1] == '>')
				cmd_node->fd_in = open(less_red(&s[i + 2]), O_WRONLY | O_APPEND | O_CREAT);
			else
				cmd_node->fd_in = open(less_red(&s[i + 1]), O_WRONLY | O_TRUNC | O_CREAT);
		}
		i++;
	}
}

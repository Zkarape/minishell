/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:13:04 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/17 14:17:09 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_or_not(char c)
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
		if (!ft_is_space(s[i]) && !red_or_not(s[i]))
			k++;
	file = malloc(sizeof(char) * k + 1);
	i = -1;
	while (++i < k)
		if (!ft_is_space(s[i]) && !red_or_not(s[i]))
			file[j++] = s[i];
	file[j] = '\0';
	return (file);
}

//char	*get_delim(char *s)
//{
//	int	i;
//
//	i = -1;
//	while ()
//}
//
//char	*heredoc(char *s, t_cmd *cmd_node)
//{
//	int	i;
//
//	i = -1;
//	while (s[++i])
//	{
//		
//	}
//}

void	func_for_reds(char *s, t_cmd *cmd_node)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			i += find_d_quote(&s[i], s[i]);
		}
		if (s[i] == '<')
		{
			if (cmd_node->fd_out != 1)
				close(cmd_node->fd_out);
			//if (s[i + 1] == '<')
			//heredoc	cmd_node->fd_out = open(less_red(&s[i + 2], O_RDONLY, );
			else
				cmd_node->fd_out = open(less_red(&s[i + 1]), O_RDONLY);
		}
		else if (s[i] == '>')
		{
			if (cmd_node->fd_in != 0)
				close(cmd_node->fd_in);
			if (s[i + 1] == '>')
				cmd_node->fd_in = open(less_red(&s[i + 2]), O_WRONLY | O_APPEND | O_CREAT);
			else
				cmd_node->fd_in = open(less_red(&s[i + 1]), O_WRONLY | O_TRUNC | O_CREAT);
		}
	}
}

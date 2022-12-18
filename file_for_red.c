/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:13:04 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/18 21:35:09 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red(char c)
{
	return (c == '<' || c == '>');
}

char	*filename_trim(char *s, int k)
{
	int		i;
	char	*file;

	i = 0;
	file = malloc(sizeof(char) * k + 1);
	while (s[i] && i < k)
	{
		file[i] = s[i];
		i++;
	}
	file[i] = '\0';
	printf("file == %s\n", file);
	return (file);
}

void	func_for_reds(char *s, t_cmd *cmd_node, int start, int end)
{
	int	i;

	i = start;
	if (s[i] == '<')
	{
		if (s[i + 1] == '<')
			cmd_node->fd_out = open(filename_trim(&s[i + 2], end - start), O_RDONLY);
		else
		{	
			if ((cmd_node->fd_out = open(filename_trim(&s[i + 1], end - start), O_RDONLY)) < 0)
				error_handling(3);
		}
	}
	else if (s[i] == '>')
	{
		if (s[i + 1] == '>')
			cmd_node->fd_in = open(filename_trim(&s[i + 2], end - start), O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
		{
			cmd_node->fd_in = open(filename_trim(&s[i + 1], end - start), O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
	}
}

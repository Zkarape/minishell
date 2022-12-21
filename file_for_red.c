/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_for_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:13:04 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/21 14:29:58 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_red(char c)
{
	return (c == '<' || c == '>');
}

char	*filename_trim(char *s, int k)
{
	int		i;
	char	*file;
	char	*file_trimmed;

	i = 0;
	if (k < 0)
		return (NULL);
	file = malloc(sizeof(char) * k + 1);
	while (s[i] && i < k)
	{
		file[i] = s[i];
		i++;
	}
	file[i] = '\0';
//	file_trimmed = file;
//	free(file);
//	file = filling_with_nulls(file_trimmed);
	return (file);
}

void func_for_reds(char *s, t_cmd *cmd_node, int start, int end, int type)
{

	int fd;

	if (type == 2)
		fd = heredoc(filename_trim(&s[start + 1], end - start));
	else if (type == 1)
		fd = open(filename_trim(&s[start + 1], end - start), O_RDONLY);
	cmd_node->fd_out = fd;
	if (type == 3)
		fd = open(filename_trim(&s[start + 1], end - start), O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (type == 4)
		fd = open(filename_trim(&s[start + 1], end - start), O_WRONLY | O_TRUNC | O_CREAT, 0644);
	cmd_node->fd_in = fd;
	// if (fd < 0)
	//	error_handling(3);
}

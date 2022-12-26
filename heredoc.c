/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/25 14:28:43 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_red *red_node)
{
	int		i;
	int		tmp_fd;
	char	*s;

	i = -1;
	s = readline("> ");
	tmp_fd = open("/Users/zkarapet/Desktop/MINISHELL_2/k5", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd < 0)
		perror("nooot openedd:: ");
	while (ft_strncmp(red_node->file, s, ft_strlen(s)) != 0 || s[0] == '\0')
	{
		ft_putstr_fd(s, tmp_fd);
		s = readline("> ");
	}
	//signal for ^C
	return (tmp_fd);
}

void	big_loop(t_cmd *cmd, t_red_lst *red_lst)
{
	int		tmp_fd;
	t_red	*cur;

	cur = red_lst->head;
	while (cur)
	{
		if (cur->type == 2)
		{
			red_lst->heredoc_k--;
			tmp_fd = heredoc(cur);
			if (red_lst->heredoc_k > 0)
				close(tmp_fd);
		}
		cur = cur->next;
	}
	cmd->fd_in = tmp_fd;
}

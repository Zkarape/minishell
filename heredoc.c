/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/24 19:58:01 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	red_lst_print(t_red_lst *list)
{
	t_red	*cur;

	cur = list->head;
	while (cur)
	{
		printf("%s %d-> ", cur->file, cur->type);
		cur = cur->next;
	}
	printf("NULL\n");
}

t_red_lst	*red_lst_construct(void)
{
	t_red_lst	*new_list;

	new_list = malloc(sizeof(t_red_lst));
	if (!new_list)
		return (NULL);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

t_red	*red_node_initialize_pro(char *file, int type)
{
	t_red	*node;

	node = malloc(sizeof(t_red));
	if (!node)
		return (NULL);
	node->type = type;
	node->file = file;
	node->next = NULL;
	return (node);
}
//
//t_red	*red_node_initialize(void)
//{
//	t_red	*node;
//
//	node = malloc(sizeof(t_red));
//	if (!node)
//		return (NULL);
//	node->type = 0;
//	node->fd = -1;
//	node->next = NULL;
//	return (node);
//}

void	red_lst_add_last(t_red_lst *list, char *file, int type)
{
	t_red	*new_node;

	new_node = red_node_initialize_pro(file, type);
	if (list->size == 0)
	{
		list->head = new_node;
		list->tail = list->head;
	}
	else
		list->tail->next = new_node;
	list->tail = new_node;
	if (type == 2)
		list->heredoc_k++;
	list->size++;
}

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

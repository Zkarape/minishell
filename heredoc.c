/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:32:53 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/20 14:42:12 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	red_lst_print(t_red_lst *list)
// {
// 	t_red	*cur;

// 	cur = list->head;
// 	while (cur)
// 	{
// 		printf("%s-> ", cur->file);
// 		cur = cur->next;
// 	}
// 	printf("NULL\n");
// }

// t_red_lst	*red_lst_construct(void)
// {
// 	t_red_lst	*new_list;

// 	new_list = malloc(sizeof(t_red_lst));
// 	if (!new_list)
// 		return (NULL);
// 	new_list->head = NULL;
// 	new_list->tail = NULL;
// 	new_list->size = 0;
// 	return (new_list);
// }

// t_red	*red_node_initialize(void)
// {
// 	t_red	*node;

// 	node = malloc(sizeof(t_red));
// 	if (!node)
// 		return (NULL);
// 	node->file = NULL;
// 	node->type = 0;
// 	node->next = NULL;
// 	return (node);
// }

// void	red_lst_add_last(t_red_lst *list)
// {
// 	t_red	*new_node;

// 	new_node = red_node_initialize();
// 	if (list->size == 0)
// 	{
// 		list->head = new_node;
// 		list->tail = list->head;
// 	}
// 	else
// 		list->tail->next = new_node;
// 	list->tail = new_node;
// 	list->size++;
// }

 int	heredoc(char *del)
 {
// 	int		i;
// 	int		tmp_fd;
// 	char	*s;

// 	i = -1;
// 	//s = readline("\n> ");
// 	tmp_fd = open("ehkbckehwdoiheb", O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (tmp_fd < 0)
// 		perror("nooot openedd:: ");
// 	while (ft_strcmp(del, s) != 0)
// 	{
// 		ft_putstr_fd(s, tmp_fd);
// 	//	s = readline("\n> ");
// 	}
// 	ft_putstr_fd(s, tmp_fd);
// 	ft_putstr_fd("\n", 1);
// 	//signa for ^C
// 	return (tmp_fd);
}

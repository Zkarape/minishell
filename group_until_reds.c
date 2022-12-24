/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_until_reds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 19:21:25 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/24 20:16:06 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checking, ><, <<<
void	cmd_lst_print(t_cmd_lst *list)
{
	t_cmd	*cur;

	cur = list->head;
	while (cur)
	{
		printf("%s-> ", cur->args);
		cur = cur->next;
	}
	printf("NULL\n");
}

t_cmd_lst	*cmd_lst_construct(void)
{
	t_cmd_lst	*new_list;

	new_list = malloc(sizeof(t_cmd_lst));
	if (!new_list)
		return (NULL);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

void	cmd_lst_add_last(t_cmd_lst *list)
{
	t_cmd	*new_node;

	new_node = cmd_node_initialize();
	if (list->size == 0)
	{
		list->head = new_node;
		list->tail = list->head;
	}
	else
		list->tail->next = new_node;
	list->tail = new_node;
	list->size++;
}

t_cmd	*cmd_node_initialize(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->fd_out = 1;
	node->fd_in = 0;
	node->next = NULL;
	node->red_lst = NULL;
	return (node);
}

void	more_reds(char *s, char c)
{
	int	i;

	i = 0;
	if (*s)
	{
		if (*(s) == c )
			error_handling(2);
		while (*s && *s == ' ')
			s++;
		if (*s == c)
			error_handling(2);
	}
}

char	*str_return_trimmed(char *s, int start, int end)
{
	char	*dst;
	int		i;

	i = -1;
	dst = malloc(sizeof(char) * (ft_strlen(s) - end + start));
	while (++i < start)
		dst[i] = s[i];
	end++;
	while (s[end])
	{
		dst[i] = s[end];
		end++;
		i++;
	} 
	dst[i] = '\0';
	return (dst);
}

int	return_type(char c, char c_next)
{
	if (c == '<')
	{
		if (c_next == '<')
			return (2);
		else
			return (1);
	}
	if (c == '>')
	{
		if (c_next == '>')
			return (3);
		else
			return (4);
	}
	return (8);
}

void	find_start_end(char *s, t_cmd *cmd_node, t_red_lst *red_lst)
{
	int		i;
	int		start;
	int		end;
	char	*str;
	int		type;

	i = -1;
	start = 0;
	end = -1;
	str = NULL;
	type = 0;
	while(s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i += find_d_quote(&s[i], s[i]);
		else if (is_red(s[i]))
		{
			str = ft_strjoin(str, s, i, end + 1);
			type = return_type(s[i], s[i + 1]);
			if (type == 2 || type == 3)
				i++;
			while (ft_is_space(s[i]))
				i++;
			start = i;
			while (!ft_is_space(s[i + 1]) && !is_red(s[i + 1]) && s[i + 1])
			 	i++;
			end = i;
			printf("trim == %s\n", filename_trim(&s[start + 1], end - start));
			red_lst_add_last(red_lst, filename_trim(&s[start + 1], end - start), type);
		}
	}
	cmd_node->args = ft_strjoin(str, s, i, end + 1);
}

void	one_cmd_init(t_node *node, t_cmd_lst *cmd_lst)
{
	char		*s;
	int			i;
	t_red_lst	*red_lst;

	i = -1;
	s = node->data;
	cmd_lst_add_last(cmd_lst);
	red_lst = red_lst_construct();
	find_start_end(s, cmd_lst->tail, red_lst);
	cmd_lst->tail->red_lst = red_lst;
	big_loop(cmd_lst->tail, red_lst);
//	red_big_loop(red_lst, cmd_lst->tail);
//	printf("trim == %s\n", );
	red_lst_print(red_lst);
	//from tail to 
}

t_cmd_lst	*grouping_with_red(t_list *pipe_group)
{
	int			i;
	t_node		*cur;
	t_cmd_lst	*cmd_lst;
	t_red_lst	*red_lst;

	i = -1;
	cmd_lst = cmd_lst_construct();
	cur = pipe_group->head;
	while (cur)
	{
		one_cmd_init(cur, cmd_lst);
		cur = cur->next;
	}
	cmd_lst_print(cmd_lst);
	return (cmd_lst);
}

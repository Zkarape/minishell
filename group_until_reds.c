/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_until_reds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:17:11 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/22 17:24:46 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ankap_checks(int *i, char *s, int type, int *start)
{
	if (type == 2 || type == 3)
		(*i)++;
	if (more_reds(&s[*i + 1], '<') || more_reds(&s[*i + 1], '>'))
		return (1);
	while (ft_is_space(s[*i + 1]))
		(*i)++;
	*start = *i;
	while (s[*i + 1] && !ft_is_space(s[*i + 1]) && !is_red(s[*i + 1]))
		(*i)++;
	return (0);
}

int	quote_forward(char *s, int i)
{
	if (s[i] == '\'' || s[i] == '"')
		i += find_last_quote(&s[i], s[i]);
	return (i);
}

int	find_start_end(char *s, t_cmd *cmd_node, t_red_lst *red_lst)
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
	while (s[++i])
	{
		i = quote_forward(s, i);
		if (is_red(s[i]))
		{
			str = ft_strjoin2(str, s, i, end + 1);
			type = return_type(s[i], s[i + 1]);
			if (ankap_checks(&i, s, type, &start))
				return (1);
			end = i;
			red_add(red_lst, file_trim(&s[start + 1], end - start, type), type);
		}
	}
	cmd_node->args = ft_strjoin2(str, s, i, end + 1);
	return (0);
}

int	one_cmd_init(t_node *node, t_cmd_lst *cmd_lst, t_args *a)
{
	char		*s;
	t_red_lst	*red_lst;

	s = node->data;
	cmd_lst_add_last(cmd_lst);
	red_lst = red_lst_construct();
	if (find_start_end(s, cmd_lst->tail, red_lst))
	{
		cmd_lst->tail->red_lst = red_lst;
		cmd_lst_destruct(&cmd_lst, cmd_lst->tail);
		return (1);
	}
	cmd_lst->tail->red_lst = red_lst;
	cmd_lst->tail->yep = last_input_work(red_lst);
	if (big_loop(cmd_lst->tail, a))
	{
		cmd_lst_destruct(&cmd_lst, cmd_lst->tail);
		return (1);
	}
	return (0);
}

t_cmd_lst	*grouping_with_red(t_list *pipe_group, t_args *a)
{
	int			i;
	t_node		*cur;
	t_cmd_lst	*cmd_lst;

	i = -1;
	cmd_lst = cmd_lst_construct();
	cur = pipe_group->head;
	while (cur)
	{
		if (one_cmd_init(cur, cmd_lst, a))
			return (NULL);
		cur = cur->next;
	}
	redirections(cmd_lst);
	return (cmd_lst);
}

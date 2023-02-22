/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_until_reds_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:14:08 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/21 22:14:52 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	more_reds(char *s, char c)
{
	if (s)
	{
		if (*s == c || *s == '\0')
		{
			ft_putstr("parse error near ");
			write(1, &c, 1);
			write(1, "\n", 1);
			return (1);
		}
		while (*s && *s == ' ')
			s++;
		if (*s == c || *s == '\0')
		{
			ft_putstr("parse error near ");
			write(1, &c, 1);
			write(1, "\n", 1);
			return (1);
		}
	}
	return (0);
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
	return (42);
}

void	redirections(t_cmd_lst *lst)
{
	t_cmd	*cur;

	cur = lst->head;
	while (cur)
	{
		if (red_big_loop(cur))
			ft_print_error_with_arg("minishell", NULL);
		cur = cur->next;
	}
}

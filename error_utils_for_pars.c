/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_for_pars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:53:19 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/21 21:53:23 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_error_checks(char *s)
{
	if (s[0] == '\0')
	{
		//g_status = 1;
		return (1);
	}
	if (!find_unquoted(s))
	{
		ft_putstr_fd("Missing quote\n", 1, 0);
		g_status = 1;
		return (1);
	}
	else if (!last_pipe_check(s))
	{
		ft_putstr_fd("Parsing error near '|'\n", 1, 0);
		g_status = 1;
		return (1);
	}
	g_status = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:49:04 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/06 21:24:32 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handling(int flag)
{
	if (flag == 0)
	{
		write(2, "parse error, quote is not closed\n", 33);
		exit(1);
	}
	else if (flag == 1)
	{
		write(2, "parse error near '|'\n", 20);
		exit(1);
	}
	else if (flag == 2)
	{
		write(2, "parse error near '<'\n", 20);
		exit(1);
	}
}

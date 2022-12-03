/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:49:04 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/01 17:57:55 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors_for_quotes(int flag)
{
	if (flag == 0)
	{
		write(2, "parse error, quote is not closed\n", 33);
		exit(1);
	}
}

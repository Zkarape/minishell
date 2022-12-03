/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:30:08 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/29 22:44:13 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

char	*read_cmd_line()
{
	char *cmd;

	cmd = readline("minishell$");
	return (cmd);
}

char	**splitting(t_cmd *pars)
{
	pars->splitted = ft_split(read_cmd_line(), '|');
}

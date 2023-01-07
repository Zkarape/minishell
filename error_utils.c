/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpetrosy <vpetrosy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:49:04 by zkarapet          #+#    #+#             */
/*   Updated: 2023/01/07 22:02:51 by vpetrosy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *str)
{
	int len;

	len = ft_strlen(str);
	write(1, str, len);
}

void	ft_print_error_and_exit(char *error, int code)
{
	ft_putstr(error);
	exit(code);
}

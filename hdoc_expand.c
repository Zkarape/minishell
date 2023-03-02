/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:20:05 by aivanyan          #+#    #+#             */
/*   Updated: 2023/03/03 00:41:04 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hdoc_expand(char *s, t_args *args)
{
	char	*str;

	str = NULL;
	args->i = 0;
	args->start = 0;
	args->hdoc_flg = 1;
	while (s && s[args->i])
	{
		args->q_idx = find_d_quotes(s, args->i);
		str = find_dollar_del(s, args, str);	
		if (s[args->i])
			args->i++;
	}
	printf("str in hdoc == %s\n", str);
	str = ft_strjoin2(str, s, args->i, args->start);
	printf("str after in hdoc == %s\n", str);
	return (str);
}

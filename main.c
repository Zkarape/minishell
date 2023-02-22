/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:35:38 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/20 13:54:17 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	a_init(t_args *a)
{
	a->env_lst = NULL;
	a->exp_lst = NULL;
	a->fd = NULL;
	a->file = NULL;
	a->pipefds = NULL;
	a->env = NULL;
	a->pids = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_args	*args;

	(void)ac;
	(void)av;
	args = malloc(sizeof(t_args));
	a_init(args);
	parsing(env, args);
	return (0);
}

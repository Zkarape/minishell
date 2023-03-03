/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:35:38 by aivanyan          #+#    #+#             */
/*   Updated: 2023/03/03 15:15:24 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_part(char *s, t_args *a, t_cmd_lst **cmd_lst, t_list **lst)
{
	if (parsing_error_checks(s))
		return (1);
	*lst = group_until_pipe(s);
	if (!lst || !(*lst))
	{
		g_status = 1;
		return (1);
	}
	*cmd_lst = grouping_with_red(*lst, a);
	if (!cmd_lst || !(*cmd_lst))
	{
		g_status = 1;
		return (1);
	}
	cmd_expanded(*cmd_lst, a);
	cmd_quote_clear(*cmd_lst);
	a->env = from_lst_to_dbl(a->env_lst);
	if ((*cmd_lst)->size == 1 && (*cmd_lst)->head->no_cmd
		&& (*cmd_lst)->head->no_cmd[0] && build((*cmd_lst)->head, a))
		return (1);
	return (0);
}

void	ctrl_d_check(char *s)
{
	if (!s)
	{
		write(1, "exit\n", 5);
		exit(g_status);
	}
}

void	exec_d_parsed(t_args *args)
{
	char		*s;
	t_list		*lst;
	t_cmd_lst	*cmd_lst;

	s = NULL;
	lst = NULL;
	cmd_lst = NULL;
	while (1)
	{
		sig_control(1);
		update_free(&cmd_lst, &lst, s, args);
		s = readline("minishell$ ");
		ctrl_d_check(s);
		if (*s)
			add_history(s);
		if (parsing_part(s, args, &cmd_lst, &lst))
		{
			args->ret = 1;
			continue ;
		}
		args->ret = pipex_main(cmd_lst, args);
	}
}

void	a_init(t_args *a, char **env_)
{
	a->env_lst = getting_env(env_);
	a->exp_lst = env_lst_construct();
	a->exp_lst = exp_cpy_env(a);
	env_lst_add_last(a->exp_lst, "declare -x ?=\"0\"");
	a->fd = NULL;
	a->file = NULL;
	a->pipefds = NULL;
	a->env = NULL;
	a->pids = NULL;
	a->ret = 1;
}

int	main(int ac, char **av, char **env)
{
	t_args	*args;

	(void)ac;
	(void)av;
	args = malloc(sizeof(t_args));
	a_init(args, env);
	exec_d_parsed(args);
//	free(args);
	return (0);
}

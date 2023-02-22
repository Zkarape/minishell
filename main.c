/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:35:38 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/23 00:02:01 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_free(t_cmd_lst **cmd_lst, t_list **lst, char *s, t_args *a)
{
	update_status(a);
	free_a(a);
	free(s);
	lst_destruct(lst);
	cmd_lst_destruct(cmd_lst, NULL);
}

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
	if ((*cmd_lst)->size == 1 && (*cmd_lst)->head->args[0]
			&& build((*cmd_lst)->head, a))
	{
		a->ret = 1;
		return (1);
	}
	return (0);
}

void	parsing(t_args *args)
{
	char		*s;
	int			ret;
	t_list		*lst;
	t_cmd_lst	*cmd_lst;

	s = NULL;
	lst = NULL;
	cmd_lst = NULL;
	ret = 0;
	while (1)
	{
		sig_control(1);
		update_free(&cmd_lst, &lst, s, args);
		s = readline("minishell$ ");
		if (!s)
		{
			write(1, "exit\n", 5);
			exit(g_status);
		}
		add_history(s);
		if (parsing_part(s, args, &cmd_lst, &lst))
			continue ;
		args->ret = pipex_main(cmd_lst, args);
		printf("args->ret == %d\n", args->ret);
	}
}

void	a_init(t_args *a, char **env_)
{
	char	*s;

	s = ft_strdup("declare -x ?=\"0\"");
	a->env_lst = getting_env(env_);
	a->exp_lst = env_lst_construct();
	a->exp_lst = exp_cpy_env(a);
	env_lst_add_last(a->exp_lst, s);
	a->fd = NULL;
	a->file = NULL;
	a->pipefds = NULL;
	a->env = NULL;
	a->pids = NULL;
	a->ret = 0;
}

int	main(int ac, char **av, char **env)
{
	t_args	*args;

	(void)ac;
	(void)av;
	args = malloc(sizeof(t_args));
	a_init(args, env);
	parsing(args);
	return (0);
}

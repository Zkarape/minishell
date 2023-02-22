/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:54:15 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/22 19:01:27 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	parsing(char **env_, t_args *args)
{
	char		*s;
	int		ret;
	t_list		*lst;
	t_cmd_lst	*cmd_lst;

	s = NULL;
	lst = NULL;
	cmd_lst = NULL;
	ret = 0;
	args->env_lst = getting_env(env_);
	args->exp_lst = env_lst_construct();
	args->exp_lst = exp_cpy_env(args);
	env_lst_add_last(args->exp_lst, "declare -x ?=\"0\"");
	while (1)
	{
		sig_control(1);
		update_status(args);
		free_a(args, ret);
		free(s);
		lst_destruct(&lst);
		cmd_lst_destruct(&cmd_lst, NULL);
		printf("heeey\n");
		s = readline("minishell$ ");
		if (!s)
		{
			write(1, "exit\n", 5);
			exit(g_status);
		}
		if (parsing_error_checks(s))
			continue ;
		add_history(s);
		lst = group_until_pipe(s);
		if (!lst)
		{
			g_status = 1;
			continue ;
		}
		cmd_lst = grouping_with_red(lst, args);
		if (!cmd_lst)
		{
			g_status = 1;
			continue ;
		}
		cmd_expanded(cmd_lst, args);
		cmd_quote_clear(cmd_lst);
		args->env = from_lst_to_dbl(args->env_lst);
		if (cmd_lst->size == 1 && cmd_lst->head->args[0]  && build(cmd_lst->head, args))
			continue ;
		ret = pipex_main(cmd_lst, args);
	}
}

void	cmd_expanded(t_cmd_lst *cmd_lst, t_args *args)
{
	t_cmd	*cur;
	char	*str;

	cur = cmd_lst->head;
	str = NULL;
	while (cur)
	{
		str = expand(cur->args, args);
		free(cur->args);
		cur->args = str;
		cur = cur->next;
	}
}

char	**no_cmd_clear(char **arr)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	while (arr[++i])
	{
		str = filling_with_nulls(arr[i]);
		free(arr[i]);
		arr[i] = str;
	}
	arr[i] = NULL;
	return (arr);
}

void	update_status(t_args *a)
{
	t_env	*cur;
	char	*itoa;
	char	*joined;
	char	*duped;

	itoa = NULL;
	joined = NULL;
	cur = a->exp_lst->head->next;
	while (cur->next)
	{
		if (cur->data[11] == '?')
		{
			remove_from_between(cur, a->exp_lst);
			break ;
		}
		cur = cur->next;
	}
	itoa = ft_itoa(g_status);
	duped = ft_strdup("declare -x ?=\""); 
	joined = ft_strjoin3(duped, itoa, "\"");
	env_lst_add_last(a->exp_lst, joined);
	free(joined);
	free(duped);
	free(itoa);
}

void	printer(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		printf("%s\n", s[i]);
	}
}

void	cmd_quote_clear(t_cmd_lst *cmd_lst)
{
	t_cmd	*cur;
	char	**arr;

	cur = cmd_lst->head;
	arr = NULL;
	while (cur)
	{
		arr = split(cur->args, ' ');
		if (!arr)
			exit(1);
		cur->no_cmd = no_cmd_clear(arr);
		cur = cur->next;
	}
}

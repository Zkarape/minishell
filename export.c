/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 21:39:09 by zkarapet          #+#    #+#             */
/*   Updated: 2023/03/02 16:20:45 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	doer(t_env *env_cur, t_args *a, int i, t_cmd *cmd)
{
	env_cur = is_in_env_or_not(a->env_lst, cmd->no_cmd[i]);
	remove_from_between(env_cur, a->env_lst);
	env_lst_add_last(a->env_lst, cmd->no_cmd[i]);
}

int	update_return(int f, t_args *a, t_cmd *cmd, int i)
{
	if (f == 2)
		return (2);
	if (f == 1)
		export_pars(cmd->no_cmd[i], a);
	return (0);
}

int	ft_export(t_cmd *cmd, t_args *a)
{
	int		i;
	int		f;
	int		q;
	char	*val;
	t_env	*env_cur;

	i = 0;
	q = 0;
	while (cmd->no_cmd[++i])
	{
		val = equality_out_of_quotes(cmd->no_cmd[i]);
		f = export_update(cmd->no_cmd[i], val, a);
		if (update_return(f, a, cmd, i) == 2)
		{
			q = 1;
			continue ;
		}
		if (val)
			doer(env_cur, a, i, cmd);
	}
	sort(a->exp_lst);
	if (!cmd->no_cmd[1])
		exp_lst_print(a->exp_lst);
	return (q);
}

void	export_pars(char *s, t_args *a)
{
	char		*data;
	char		*unquoted;
	char		*quoted;
	char		*retval;
	char		*duped;

	data = NULL;
	unquoted = equality_out_of_quotes(s);
	quoted = adding_quotes(unquoted);
	a->start = ft_strlen(quoted);
	a->end = 0;
	a->len = ft_strlen(s) - ft_strlen(unquoted);
	data = ft_strjoin(s, quoted, a);
	a->start = ft_strlen(data);
	a->end = 0;
	a->len = 11;
	duped = ft_strdup("declare -x ");
	retval = ft_strjoin(duped, data, a);
	env_lst_add_last(a->exp_lst, retval);
	free(quoted);
	free(data);
	free(retval);
	free(duped);
}

int	export_update(char *arg, char *arg_val, t_args *a)
{
	t_env	*cur;

	a->k = 0;
	cur = a->exp_lst->head->next;
	while (cur->next)
	{
		if (error_checks_for_var(arg, until_equal_sign(arg), 1))
			return (2);
		if (arg_val)
		{
			if (!cmpfree(before(arg), before(&cur->data[11]), 1))
			{
				remove_from_between(cur, a->exp_lst);
				return (1);
			}
			a->k++;
		}
		else
			if (cmpfree(before(arg), before(&cur->data[11]), 1))
				a->k++;
		cur = cur->next;
	}
	if (a->k == a->exp_lst->size)
		return (1);
	return (0);
}

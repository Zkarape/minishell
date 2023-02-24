/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 21:39:09 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/24 19:07:36 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_cmd *cmd, t_args *a)
{
	int		i;
	int		f;
	char	*val;
	t_env	*env_cur;

	i = 0;
	while (cmd->no_cmd[++i])
	{
		val = equality_out_of_quotes(cmd->no_cmd[i]);
		f = export_update(cmd->no_cmd[i], val, a);
		if (f == 2)
			return (1);
		if (f == 1)
			export_pars(cmd->no_cmd[i], a);
		if (val)
		{
			env_cur = is_in_env_or_not(a->env_lst, cmd->no_cmd[i]);
			remove_from_between(env_cur, a->env_lst);
			env_lst_add_last(a->env_lst, cmd->no_cmd[i]);
		}
	}
	sort(a->exp_lst);
	if (!cmd->no_cmd[1])
		exp_lst_print(a->exp_lst);
	return (0);
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

t_env_lst	*exp_cpy_env(t_args *a)
{
	t_env		*cur;

	cur = a->env_lst->head->next;
	while (cur->next)
	{
		export_pars(cur->data, a);
		cur = cur->next;
	}
	return (a->exp_lst);
}

int	cmp_remove(int k, t_env *cur, t_env_lst *exp_lst, char *arg)
{
	if (!ft_strncmp(&cur->data[11], arg, k))
	{
		remove_from_between(cur, exp_lst);
		return (1);
	}
	return (0);
}

int	export_update(char *arg, char *arg_val, t_args *a)
{
	t_env	*cur;
	int		k;

	k = 0;
	cur = a->exp_lst->head->next;
	while (cur->next)
	{
		if (error_checks_for_var(arg, until_equal_sign(arg), 1))
			return (2);
		if (arg_val)
		{
			if (!ft_strcmp_with_free(before_equal(arg), before_equal(&cur->data[11])))
			{
				remove_from_between(cur, a->exp_lst);
				return (1);
			}
		}
		else
			if (ft_strcmp_with_free(before_equal(arg), before_equal(&cur->data[11])))
				k++;
		cur = cur->next;
	}
	if (k == a->exp_lst->size)
		return (1);
	return (0);
}

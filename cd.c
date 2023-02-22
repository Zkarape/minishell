/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 22:56:51 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/16 00:54:49 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(char *var_name, char *cwd, t_args *a)
{
	char	*str;
	t_env	*cur;
	t_env	*cur_exp;

	str = ft_strjoin_m(var_name, cwd);
	cur = is_in_env_or_not(a->env_lst, str);
	cur_exp = is_in_exp_or_not(a->exp_lst, str);
	if (cur)
		remove_from_between(cur, a->env_lst);
	if (cur_exp)
		remove_from_between(cur_exp, a->exp_lst);
	export_pars(str, a);
	env_lst_add_last(a->env_lst, str);
}

int	cd(char *path, char **env, t_args *a)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	change_pwd("OLDPWD=", cwd, a);
	if (!path)
	{
		if (chdir(get_environment("HOME=", env)))
			ft_print_error_with_arg("cd", path);
		cwd = getcwd(NULL, 0);
		change_pwd("PWD=", cwd, a);
	}
	else
	{
		if (chdir(path))
			ft_print_error_with_arg("cd", path);
		cwd = getcwd(NULL, 0);
		change_pwd("PWD=", cwd, a);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:05:06 by zkarapet          #+#    #+#             */
/*   Updated: 2023/03/03 14:30:56 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_checks_for_var(char *s, int until, int flag)
{
	int	i;

	i = 0;
	if ((!s || s[0] == '_') && flag)
		return (0);
	if (!is_alpha(s[0]))
	{
		ft_putstr(s);
		ft_putstr(": not a valid identifier\n");
		return (1);
	}
	while (s[i] && i < until)
	{
		if (!is_num(s[i]) && s[i] != '_' && !is_alpha(s[i]))
		{
			ft_putstr(s);
			ft_putstr(": not a valid identifier\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	env(t_env_lst *env_lst, char *arg, char **envv)
{
	if (!get_environment("PATH=", envv))
	{
		ft_putstr_fd("env: No such file or directory\n", 2, 0);
		return (1);
	}
	if (arg)
	{
		ft_print_error_with_arg("env", arg);
		return (1);
	}
	env_lst_print(env_lst);
	return (0);
}

int	pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("pwd error\n");
		return (1);
	}
	return (0);
}

int	cmpfree(char *s1, char *s2, int f)
{
	int	i;
	int	res;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	res = s1[i] - s2[i];
	free(s1);
	if (f)
		free(s2);
	return (res);
}

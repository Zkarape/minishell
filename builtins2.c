/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:05:06 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/24 00:19:36 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_checks_for_var(char *s, int until, int flag)
{
	int	i;

	i = 0;
	printf("until == %d, i == %c\n", until, s[until]);
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
			printf("aaaaaaaaaaaaaaa\n");
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
		ft_putstr("env: No such file or directory\n");
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

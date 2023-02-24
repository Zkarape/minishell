/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:08:23 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/24 19:35:13 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	until_equal_sign(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '=')
		i++;
	return (i);
}

char	*after_equal_str(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '=')
		i++;
	return (&s[i]);
}

char	*before_equal(char *s)
{
	return (ft_substr_m(s, 0, until_equal_sign(s)));
}

int	cmp_len(char *cleaned_file, char *s)
{
	int	len;

	len = ft_strlen(s);
	if (ft_strlen(cleaned_file) > ft_strlen(s))
		len = ft_strlen(cleaned_file);
	return (len);
}

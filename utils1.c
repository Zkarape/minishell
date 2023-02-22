/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:35:56 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/18 19:44:28 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && ((unsigned char)s1[i] || (unsigned char)s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}	
	return (*s1 - *s2);
}

char	*ft_strcpy(char *dest, char *src)
{
	char	*temp;

	temp = dest;
	while (src && *src)
	{
		*temp = *src;
		src++;
		temp++;
	}
	*temp = '\0';
	return (dest);
}

char	**from_lst_to_dbl(t_env_lst *env_lst)
{
	int		i;
	char	**arr;
	t_env	*env;

	i = 0;
	env = env_lst->head->next;
	arr = malloc(sizeof(char *) * (env_lst->size + 1));
	if (!arr)
		exit(1);
	while (env->next)
	{
		arr[i] = malloc(sizeof(char) * (ft_strlen(env->data) + 1));
		if (ft_check_alloc(arr, arr[i], i))
			exit(1);
		ft_strcpy(arr[i++], env->data);
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

char	*ft_str_tolower(char **s)
{
	int		i;

	i = -1;
	while ((*s)[++i])
	{
		if (!ft_tolower((*s)[i]))
			ft_tolower((*s)[i]);
	}
	return (*s);
}

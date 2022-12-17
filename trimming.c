/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimming.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:13:28 by aivanyan          #+#    #+#             */
/*   Updated: 2022/12/17 13:00:48 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

//char	*str_return_trimmed(char *s, int start, int end)
//{
//	char	*dst;
//	int		i;
//
//	i = -1;
//	dst = malloc(sizeof(char) * (ft_strlen(s) - end + start));
//	printf("%d\n", ft_strlen(s) - end + start);
//	while (++i < start)
//		dst[i] = s[i];
//	end++;
//	while (s[end])
//	{
//		dst[i] = s[end];
//		end++;
//		i++;
//	} 
//	dst[i] = '\0';
//	return (dst);
//}

t_cmd	*cmd_node_initializer(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->fd_out = 1;
	node->fd_in = 0;
	node->quoted = 0;
	node->next = NULL;
	return (node);
}

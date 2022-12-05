/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimming.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:13:28 by aivanyan          #+#    #+#             */
/*   Updated: 2022/12/04 18:34:50 by aivanyan         ###   ########.fr       */
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

char	*str_return_trimmed(char *s, int start, int end)
{
	char	*dst;
	int		i;

	i = -1;
	dst = malloc(sizeof(char) * (ft_strlen(s) - end + start));
	printf("%d\n", ft_strlen(s) - end + start);
	while (++i < start)
		dst[i] = s[i];
	end++;
	while (s[end])
	{
		dst[i] = s[end];
		end++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
//splitting with ' ' then check, if there is only < in any string of char **, then get the next string as a file for <, if not then the whole string is <file
// int	d_end_of_redirection(char *s, int start)
// {
// 	int	i;

// 	i = start - 1;
// 	while (s[++i])
// 	{
// 		while (s[i] == ' ' || s[i] == '\t')
// 			i++;
// 		while (s[i])
// 		{
// 			/* code */
// 		}
		
// 	}
// }
// void	cleaner_from_st_to_end(char *s, int start, int end)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i] < start)
// 		;
// 	while (s[])
// 	{
// 		/* code */
// 	}
	
// }

int main(int ac, char **av)
{
	cleaner_from_st_to_end(av[1], 2, 5);
	//printf("s == %s\n", cleaner_from_st_to_end(av[1], 2, 5));
}
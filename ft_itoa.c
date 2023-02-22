/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:18:17 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/14 19:18:30 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_digit_count(long num)
{
	int	count;

	count = (num <= 0);
	while (num)
	{
		count++;
		num /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;
	long	num;

	num = n;
	count = ft_digit_count(num);
	str = malloc((count + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[count--] = '\0';
	if (num == 0)
		str[count] = '0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		str[count--] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

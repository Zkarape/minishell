/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   summerize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:13:41 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/04 12:15:39 by aivanyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

//list for grouping

typedef struct s_node
{
	char	*data;
	struct	s_node *next;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_list;

t_list	*lst_construct(void)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

t_node	*node_initialize(char *data)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

void	lst_add_last(t_list *list, char *data)
{
	t_node	*new_node;

	new_node = node_initialize(data);
	if (list->size == 0)
	{
		list->head = new_node;
		list->tail = list->head;
	}
	else
		list->tail->next = new_node;
	list->tail = new_node;
	list->size++;
}

void	lst_print(t_list *list)
{
	t_node	*cur;

	cur = list->head;
	while (cur)
	{
		printf("%s-> ", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}
/////////////////////////////////

char	*ft_substr_m(char *s, int start, int end)
{
	char *dst;
	int	i;

	i = 0;
	dst = malloc(sizeof(char) * (end - start + 1));
	while (start < end)
	{
		dst[i] = s[start];
		i++;
	}
	// null termination missing : WARNING
	dst[i] = '\0';
	return (dst);
}

/*
char	quote_detection(char c)
{
	if (c == '"')
		return (c);
	else if (c == '\'')
		return (c);
	else
		return ('a');
}

*/

int	find_d_quote(char *s, char quote)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == quote)
			return (i);
	return (0); // WARNING CHANGED
}
/*
int	until_d_next_quote(char quote, char *s)
{
	int	start;

	start = find_d_quote(s, quote) + 1;
	if (quote != 'a')
	{
		while (s[start] && s[start] != quote)
			start++;
	}
	return (start);
}

int	from_d_end(char quote, char *s)
{
	int	end;
	int	start2;

	start2 = until_d_next_quote(quote, s);
	end = 0;
	
}
*/

void	group_until_pipe(char *s)
{
	int		i;
	int		start;
	t_list	*group;

	i = 0;
	start = 0;
	group = lst_construct();
	if (s[0] == '|')
		error_handling(1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i += find_d_quote(&s[i], s[i]);
		else if (s[i] == '|')
		{
			lst_add_last(group, ft_substr_m(s, start, i));
			start = i + 1; // start in else if not outside : WARNING
		}
		i++;
	}
	lst_print(group);
}

int main()
{
	group_until_pipe(readline("c2r2s5"));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimming.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:13:28 by aivanyan          #+#    #+#             */
/*   Updated: 2022/12/06 22:18:22 by zkarapet         ###   ########.fr       */
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

t_listik_cmd	*lst_construct(void)
{
	t_listik_cmd	*new_list;

	new_list = malloc(sizeof(t_listik_cmd));
	if (!new_list)
		return (NULL);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

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

//char	less_or_great(char c)
//{
//	if (c == '<')
//		return (c);
//	else if (c == '>')
//		return (c);
//}

int	red_or_not_ttq(char **sp, t_cmd *node)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (sp[++i])
	{
		if (sp[i][0] == '<')
		{
			if (sp[i][1] == '\0' && sp[i + 1])
			{
				if (sp[i + 1][0] == '<')
					error_handling(2);
			//	else if (sp[i][1] == '<')
			//<< add near here
				if (node->fd_out != 1)
					close(node->fd_out);
				node->fd_out = open(sp[i + 1], O_RDONLY);
				k++;
			}
			else
			{
				if (node->fd_out != 1)
					close(node->fd_out);
				node->fd_out = open(*(sp + i) + 1, O_RDONLY);
				k++;
			}
		}
		else if (sp[i][0] == '>')
		{
			if (sp[i][1] == '\0' && sp[i + 1])
			{
				if (sp[i + 1][0] == '>')
					error_handling(2);
				if (node->fd_in)
					close(node->fd_in);
				node->fd_in = open(sp[i + 1], O_RDONLY);
				k++;
			}
			else if (sp[i][1] == '>' && sp[i + 1])
			{
				if (!sp[i][2])
				{
					if (node->fd_in)
						close(node->fd_in);
					node->fd_in = open(sp[i + 1], O_WRONLY | O_TRUNC);
					k++;
				}
				else
				{	
					if (node->fd_in)
						close(node->fd_in);
					node->fd_in = open(*(sp + i) + 2, O_WRONLY | O_TRUNC);
					k++;
				}
			}
			else
			{
				if (node->fd_in)
					close(node->fd_in);
				node->fd_in = open(*(sp + i) + 1, O_WRONLY);
				k++;
			}
		}
	}
}

void	filling_node(char **splitted_data)
{
	t_cmd	*node;
	int		i;

	node = cmd_node_initializer();
	i = -1;
	while (splitted_data[++i])
	{
		if ()
	}
}

void	defining_cmd_list(t_listik_cmd *cmd, char **splitted_data)
{
	
}

char	*iterating_to_split_by_sp(t_list *listik, t_listik_cmd *cmd)
{
	t_node	*cur;

	cur = NULL;
	if (listik && listik->head)
	{
		cur = listik->head;
		while (cur)
		{
			ft_split(cur->data);
			cur = cur->next;
		}
	}
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

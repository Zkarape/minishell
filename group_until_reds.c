#include "minishell.h"

//checking, ><, <<<
void	cmd_lst_print(t_cmd_lst *list)
{
	t_cmd	*cur;

	cur = list->head;
	while (cur)
	{
		printf("%s-> ", cur->args);
		cur = cur->next;
	}
	printf("NULL\n");
}

t_cmd_lst	*cmd_lst_construct(void)
{
	t_cmd_lst	*new_list;

	new_list = malloc(sizeof(t_cmd_lst));
	if (!new_list)
		return (NULL);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

void	cmd_lst_add_last(t_cmd_lst *list)
{
	t_cmd	*new_node;

	new_node = cmd_node_initialize();
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

t_cmd	*cmd_node_initialize(void)
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
	node->head_red = NULL;
	return (node);
}

void	more_reds(char *s, char c)
{
	int	i;

	i = 0;
	if (*s)
	{
		if (*(s) == c )
			error_handling(2);
		while (*s && *s == ' ')
			s++;
		if (*s == c)
			error_handling(2);
	}
}

char	*str_return_trimmed(char *s, int start, int end)
{
	char	*dst;
	int		i;

	i = -1;
	dst = malloc(sizeof(char) * (ft_strlen(s) - end + start));
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
int	return_type(char c, char c_next)
{
	if (c == '<')
	{
		if (c_next == '<')
			return (2);
		else
			return (1);
	}
	if (c == '>')
	{
		if (c_next == '>')
			return (3);
		else
			return (4);
	}
};

int	find_start1_end1(char *s, t_cmd *cmd_node)
{
	int	i;
	int	type;
	int	start1;
	int	end1;

	i = 0;
	start1 = 0;
	end1 = 0;
	type = return_type(s[i], s[i + 1]);
	if (type == 2 || type == 3)
		i++;
	start1 = ++i;
	while (ft_is_space(s[i]))
		i++;
	while (!ft_is_space(s[i]) && !is_red(s[i]) && s[i])
		i++;
	end1 = i - 1;
	func_for_reds(s, cmd_node, start1, end1, type);
	return (i);
}

int	find_start2_end2(char *s, t_cmd *cmd_node, int i)
{
	int	start2;
	int	end2;

	start2 = i;
	while (ft_is_space(s[i]))
		i++;
	while (!ft_is_space(s[i]) && !is_red(s[i]) && s[i])
		i++;
	end2 = i - 1;
	ft_strjoin(cmd_node->args, s, end2, start2);
	return (i);
}

void	find_start_end(char *s, t_cmd *cmd_node)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (is_red(s[i]))
			i += find_start1_end1(&s[i], cmd_node);
		else
			i = find_start2_end2(s, cmd_node, i);
	}
}	
// void	find_start_end(char *s, t_cmd *cmd_node)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	char	*str;
// 	int		type;

// 	i = -1;
// 	start = 0;
// 	end = 0;
// 	str = NULL;
// 	type = 0;
// 	while(s[++i])
// 	{
// 		if (s[i] == '\'' || s[i] == '"')
// 			i += find_d_quote(&s[i], s[i]);
// 		else if (is_red(s[i]))
// 		{
// 			str = ft_strjoin(str, s, i, end);
// 			type = return_type(s[i], s[i + 1]);
// 			if (type == 2 || type == 3)
// 				i++;
// 			while (ft_is_space(s[i + 1]))
// 				i++;
// 			start = i;
// 			if (ft_is_space(s[i]))
// 				i++;
// 			// while (!ft_is_space(s[i]) && 
// 			// 	!is_red(s[i + 1]) && s[i])
// 			// 	i++;
// 			end = i;
// 			printf("start + 1 = %c\n", s[start + 1]);
// 			printf("end = %c\n", s[end]);
// 			printf("start = %d\n", start);
// 			printf("end = %d\n", end - 1);
// 			func_for_reds(s, cmd_node, start, end - 1, type); // hanel space
// 		}
// 	}
// 	cmd_node->args = ft_strjoin(str, s, i, end);
// }
// void	find_start_end(char *s, t_cmd *cmd_node)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	char	*str;

// 	i = -1;
// 	str = NULL;
// 	end = 0;
// 	start = 0;
// 	while (s[++i])
// 	{
// 		if (s[i] == '\'' || s[i] == '"')
// 			i += find_d_quote(&s[i], s[i]);
// 		else if (is_red(s[i]))
// 		{
// 			start = i;
// 			printf("s[end] = %c\n", s[end]);
// 			if (!is_red(s[end]))
// 				str = ft_strjoin(str, s, start, end);
// 			printf("join %s\n", str);
// 			while (ft_is_space(s[i]))
// 				i++;
// 			while (!ft_is_space(s[i]) && s[i])
// 			{
// 				if (is_red(s[i]) && is_red(s[i + 1]))
// 					break;
// 				i++;
// 			}
// 			end = i;
// 		}
// 		while (ft_is_space(s[start]))
// 			start++;
// 		func_for_reds(s, cmd_node, start, end);
// 	}
// 	cmd_node->args = ft_strjoin(str, s, i, end);
// 	printf("afterafter tail %s\n", cmd_node->args);
// }

void	one_cmd_init(t_node *node, t_cmd_lst *cmd_lst)
{
	char	*s;
	int		i;

	i = -1;
	s = node->data;
	cmd_lst_add_last(cmd_lst);
	printf("before tail%s\n", cmd_lst->tail->args);
	find_start_end(s, cmd_lst->tail);
	printf("after tail%s\n", cmd_lst->tail->args);
}

t_cmd_lst	*grouping_with_red(t_list *pipe_group)
{
	int			i;
	t_node		*cur;
	t_cmd_lst	*cmd_lst;

	i = -1;
	cmd_lst = cmd_lst_construct();
	cur = pipe_group->head;
	while (cur)
	{
		one_cmd_init(cur, cmd_lst);
		cur = cur->next;
	}
	cmd_lst_print(cmd_lst);
	return (cmd_lst);
}

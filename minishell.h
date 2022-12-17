/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:37:36 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/17 22:20:40 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

typedef struct s_node
{
	char	*data;
	struct	s_node *next;
}	t_node;

typedef	struct	s_cmd
{
	char	*args;
	int		fd_out;
	int		fd_in;
	int		quoted;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_cmd_lst
{
	t_cmd	*head;
	t_cmd	*tail;
	int		size;
}	t_cmd_lst;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_list;

// typedef struct s_cmd
// {
	
// };
//ft_split
int		ft_is_space(char c);
int		word_cpy(char *s_m, char *s, char quote);

//quote_checks
int		find_d_unquote(char *s);
char	*strcpy_noquotes(char *str, char c);

//summerize.c
t_list	*group_until_pipe(char *s);
void	more_pipes(char *s);
char	*ft_substr_m(char *s, int start, int end);
int		find_d_quote(char *s, char quote);
void	lst_print(t_list *list);
void	lst_add_last(t_list *list, char *data);
t_node	*node_initialize(char *data);
t_list	*lst_construct(void);
int		find_d_quote(char *s, char quote);

//file_for_red.c
char	*less_red(char *s);
int		is_red(char c);
void	func_for_reds(char *s, t_cmd *cmd_node, int start, int end);

//error_cases
void	error_handling(int flag);

//group_until_reds.c
t_cmd_lst	*cmd_lst_construct(void);
void		cmd_lst_add_last(t_cmd_lst *list);
t_cmd_lst		*grouping_with_red(t_list *pipe_group);
void		one_cmd_init(t_node *node, t_cmd_lst *cmd_lst);
void		find_start_end(char *s, int *start, int *end);
t_cmd		*cmd_node_initialize(void);
char		*str_return_trimmed(char *s, int start, int end);
//trimming
int		ft_strlen(char *s);
t_list	*lst_construct(void);
# endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:37:36 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/17 14:19:15 by zkarapet         ###   ########.fr       */
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
	char	**args;
	int		fd_out;
	int		fd_in;
	int		quoted;
	struct s_cmd *next;
}	t_cmd;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_list;

// typedef struct s_cmd
// {
	
// };
// nor.c
int		ft_is_space(char c);
char	*less_red(char *s);
void	func_for_reds(char *s, t_cmd *cmd_node);
t_cmd	*cmd_node_initializer(void);
//ft_split
int		word_cpy(char *s_m, char *s, char quote);

//quote_checks
int		find_d_unquote(char *s);
char	*strcpy_noquotes(char *str, char c);

//summerize.c
void	group_until_pipe(char *s, t_list *group);
void	lst_print(t_list *list);
int		find_d_quote(char *s, char quote);
t_list	*lst_construct(void);

//error_cases
void	error_handling(int flag);

//trimming
int		ft_strlen(char *s);
t_list	*lst_construct(void);
t_cmd	*cmd_node_initializer(void);
# endif

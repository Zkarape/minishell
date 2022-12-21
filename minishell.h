/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:37:36 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/21 14:52:37 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TMPFILENAME "hjdsgcibdcjkeuhckjcjkcdjdkjjscjkdjkcjdj"

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef	struct	s_red
{
	int				type;
	char			*file;
	struct s_red	*next;
}	t_red;

typedef struct s_node
{
	char			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_red_lst
{
	t_red	*head;
	t_red	*tail;
	int		size;
}	t_red_lst;

typedef	struct	s_cmd
{
	char				*args;
	int					fd_out;
	int					fd_in;
	struct s_cmd		*next;
	struct s_red_lst	*red_lst;
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
char	*filename_trim(char *s, int k);
char	*less_red(char *s, int st, int end);
int		is_red(char c);
void	func_for_reds(char *s, t_cmd *cmd_node, int start, int end, int type);

//error_cases
void	error_handling(int flag);

//group_until_reds.c
t_cmd_lst		*cmd_lst_construct(void);
void			cmd_lst_add_last(t_cmd_lst *list);
t_cmd_lst		*grouping_with_red(t_list *pipe_group);
void			one_cmd_init(t_node *node, t_cmd_lst *cmd_lst);
void			find_start_end(char *s, t_cmd *cmd, t_red_lst *red_lst);
t_cmd			*cmd_node_initialize(void);
char			*str_return_trimmed(char *s, int start, int end);
int				return_type(char c, char c_next);
//utils.c
char	*ft_strjoin(char *s1, char *s2, int start, int end);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *s);
//trimming
t_list	*lst_construct(void);
//filling_with_nulls.c
char	*filling_without_c(char *s, char c, int len, int count);
char	*filling_with_nulls(char *s);
//heredoc.c
int			heredoc(char *del);
void		red_lst_print(t_red_lst *list);
t_red_lst	*red_lst_construct(void);
t_red		*red_node_initialize(void);
t_red		*red_node_initialize_pro(char *file, int type);
void		red_lst_add_last(t_red_lst *list, char *file, int type);
#endif

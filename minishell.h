/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <aivanyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:37:36 by zkarapet          #+#    #+#             */
/*   Updated: 2022/12/27 21:11:18 by zkarapet         ###   ########.fr       */
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
	int		heredoc_k;
}	t_red_lst;

typedef	struct	s_cmd
{
	char				*args;
	int					fd_out;
	int					fd_in;
	struct s_cmd		*next;
	struct s_red_lst	*red_lst;
}	t_cmd;

typedef struct	s_env
{
	char			*data;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

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

typedef struct	s_env_lst
{
	t_env	*head;
	t_env	*tail;
	int		size;
}	t_env_lst;

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
void	func_for_reds(t_cmd *cmd_node, t_red *red_node);
void	red_big_loop(t_red_lst *red_lst, t_cmd *cmd);

//error_cases
void	error_handling(int flag);

//group_until_reds.c
t_cmd_lst		*cmd_lst_construct(void);
void			cmd_lst_print(t_cmd_lst *list);
void			cmd_lst_add_last(t_cmd_lst *list);
t_cmd_lst		*grouping_with_red(t_list *pipe_group);
void			one_cmd_init(t_node *node, t_cmd_lst *cmd_lst);
void			find_start_end(char *s, t_cmd *cmd, t_red_lst *red_lst);
t_cmd			*cmd_node_initialize(void);
char			*str_return_trimmed(char *s, int start, int end, char *val);
int				return_type(char c, char c_next);
//utils.c
char	*ft_strjoin(char *s1, char *s2, int start, int end);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *s);
//trimming
t_list	*lst_construct(void);
//filling_with_nulls.c
char	*filling_without_c(char *s, char c, int len, int count);
char	*filling_with_nulls(char *s);
//heredoc.c
int			heredoc(t_red *red_node);
void		red_lst_print(t_red_lst *list);
t_red_lst	*red_lst_construct(void);
t_red		*red_node_initialize(void);
t_red		*red_node_initialize_pro(char *file, int type);
void		red_lst_add_last(t_red_lst *list, char *file, int type);
void		big_loop(t_cmd *cmd_node, t_red_lst *red_lst);

//expanding.c
int		is_quote(char c);
int		find_d_quotes(char *s, int i);
int		if_is_dollar(char *s, char **del, int i, int start, t_env_lst *env_lst);
void	expand(char *s, t_cmd *cmd_node, t_env_lst *env_lst);
int		find_dollar_del(char *s, char **str, int i, int q_idx, int *start, t_env_lst *env_lst);

//env_lst_construct.c
void		remove_from_between(t_env *env, t_env_lst *env_lst);
void		add_between(t_env *predecessor, t_env *successor, char *data);
t_env		*env_initialize(char *data, t_env *next, t_env *prev);
t_env_lst	*env_lst_construct(void);
void		env_lst_add_last(t_env_lst *list, char *data);
t_env		*env_def_initialize(void);
void		env_lst_print(t_env_lst *list);

//environment.c
t_env_lst	*getting_env(char **env);
#endif

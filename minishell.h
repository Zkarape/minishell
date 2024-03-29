/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:07:49 by zkarapet          #+#    #+#             */
/*   Updated: 2023/03/04 15:42:50 by zkarapet         ###   ########.fr       */
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
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include "readline/readline.h"
# include "readline/history.h"

# define HEREDOC 2
# define INPUT_REDIRECTION 1
# define OUTPUT_REDIRECTION 4
# define APPEND_REDIRECTION 3

extern int	g_status;

typedef struct s_red
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

typedef struct s_cmd
{
	char				*args;
	char				**no_cmd;
	int					fd_out;
	int					fd_in;
	int					yep;
	struct s_cmd		*next;
	struct s_red_lst	*red_lst;
	int					hdoc_fd;
}	t_cmd;

typedef struct s_env
{
	char			*data;
	int				idx;
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

typedef struct s_env_lst
{
	t_env	*head;
	t_env	*tail;
	int		size;
}	t_env_lst;

typedef struct s_args
{
	int				i;
	int				k;
	int				ret;
	int				q_idx;
	int				start;
	int				end;
	int				len;
	int				exp_start;
	int				hdoc_flg;
	int				hdoc_size;
	int				*fd;
	int				size;
	int				cmd_lst_size;
	int				(*pipefds)[2];
	char			*file;
	char			**env;
	pid_t			*pids;
	t_env_lst		*env_lst;
	t_env_lst		*exp_lst;
	struct termios	term;
}	t_args;

//group_until_reds.c
int			find_start_end(char *s, t_cmd *cmd, t_red_lst *red_lst);
int			one_cmd_init(t_node *node, t_cmd_lst *cmd_lst, t_args *a);
t_cmd_lst	*grouping_with_red(t_list *pipe_group, t_args *a);
//group_until_reds_utils.c
int			more_reds(char *s, char c);
int			return_type(char c, char c_next);
void		redirections(t_cmd_lst *lst);
//cmd_lst_construct.c
t_cmd_lst	*cmd_lst_construct(void);
void		cmd_lst_print(t_cmd_lst *list);
void		cmd_lst_add_last(t_cmd_lst *list);
t_cmd		*cmd_node_initialize(void);
//heredoc.c
void		closing_hdoc(int fd[2], t_cmd *cmd, int flag);
int			heredoc(t_cmd *cmd, t_args *a);
int			big_loop(t_cmd *cmd, t_args *a);
//hdoc_expand.c
char *hdoc_expand(char *s, t_args *args);

//pipex_utils.c
int			pipefds_check(int (*pipefds)[2], int i, t_cmd *cur);
void		processing_status(t_args *a, int size);
void		checking_fork(t_args *a, pid_t forking, int i);
//pipex.c
void		execute(t_cmd *cmd, char **env);
int			forking_separately(t_args *a, t_cmd *cur, int size);
pid_t		forking(int pipefd_in, int pipefd_out, t_cmd *cur, t_args *a);
void		process(int pipefd_in, int pipefd_out, t_cmd *cur, t_args *a);
int			pipex_main(t_cmd_lst *cmd_lst, t_args *a);
int			pipe_error(int pip);
//utils0.c
int			hdoc_pipe_check(int fd[2], t_cmd *cmd);
int			is_num(char c);
int			is_alpha(char c);
int			ft_tolower(int c);
void		close_pipefds(int (*pipefds)[2], int i, t_cmd *cur, int cl_cur);
//utils1.c
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *s1, char *s2);
char		**from_lst_to_dbl(t_env_lst *env_lst);
char		*ft_str_tolower(char **s);

//utils.c
int			ft_is_space(char c);
void		ft_putstr_fd(char *s, int fd, int fl);
int			ft_strlen(char *s);
int			ft_tolower(int c);
void		closing(t_cmd *cur);

//environment.c
t_env_lst	*getting_env(char **env);
char		*get_environment(char *name, char **env);

//joins.c
char		*ft_strjoin_m(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2, t_args *a);
char		*ft_strjoin2(char *s1, char *s2, int start, int end);
char		*ft_strjoin3(char *str1, char *str2, char *str3);

//split.c
static int	ft_count(char *str, char c);
static char	*ft_start(char *s, char c);
static char	*ft_end(char *s, char c);
char		**split(char *s, char c);

//split_utils.c
int			ft_check_alloc(char **split, char *str, int index);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlcpy(char *dest, char *src, size_t dstsize);
void		*ft_calloc(size_t count, size_t size);

//split_utils0.c
char		*ft_strdup(char *s1);
void		*ft_memcpy(void *dest, void *src, size_t n);

//split_utils.c
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlcpy(char *dest, char *src, size_t dstsize);
void		*ft_memset(void *b, int c, size_t len);
int			ft_check_alloc(char **split, char *str, int index);

//summerize.c
t_list		*group_until_pipe(char *s);
int			more_pipes(char *s);
char		*ft_substr_m(char *s, int start, int end);
int			find_last_quote(char *s, char quote);
int			pipe_check(char *s, t_list *group, int i, int f);

//quote_checks
char		*removing_fst_lst_dbl_quotes(char *s);
int			find_d_unquote(char *s);
char		*strcpy_noquotes(char *str, char c);

//summerize.c
void		lst_print(t_list *list);
void		lst_add_last(t_list *list, char *data);
t_node		*node_initialize(char *data);
t_list		*lst_construct(void);
int			find_last_quote_with_full_index(char *s, char quote, int i);

//file_for_red.c
char		*file_trim(char *s, int k, int type);
int			is_red(char c);
int			func_for_reds(t_cmd *cmd_node, t_red *red_node);
int			red_big_loop(t_cmd *cmd);
void		close_in_out(int fd);

//error_cases
int			parsing_error_checks(char *s);
void		ft_print_error_and_exit(char *error, int code);
void		ft_print_error_with_arg(char *cmd, char *arg);
void		ft_putstr(char *str);
void		dup_error(int du);


void		ft_putstr_fd(char *s, int fd, int fl);
int			ft_strlen(char *s);
void		closing(t_cmd *cur);
//trimming
t_list		*lst_construct(void);
//filling_with_nulls.c
char		*clean_fst_last(char *s);
char		*filling_without_c(char *s, char c, int len, int count);
char		*filling_with_nulls(char *s);

//red_lst_construct.c
void		red_lst_print(t_red_lst *list);
t_red_lst	*red_lst_construct(void);
t_red		*red_node_initialize(void);
t_red		*red_node_initialize_pro(char *file, int type);
void		red_add(t_red_lst *list, char *file, int type);

//expanding.c
int			find_first_quote(char *s, int i);
int			find_d_quotes(char *s, int i);
char		*find_start_end_for_expand(t_args *a, char *s);
char		*expand(char *s, t_args *args);
char		*hdoc_expand(char *s, t_args *args);
char		*find_dollar_del(char *s, t_args *a, char *str);
//expanding_utils.c
int			find_d_quote2(char *s, char quote, int i);
char		*get_exp(t_env_lst *exp_lst, char *del);
char		*get_env(t_env_lst *env_lst, char *del);
int			is_quote(char c);
//env_lst_construct.c
void		remove_from_between(t_env *env, t_env_lst *env_lst);
void		add_between(t_env *predecessor, t_env *successor, char *data);
t_env		*env_initialize(char *data, t_env *next, t_env *prev);
t_env_lst	*env_lst_construct(void);
void		env_lst_add_last(t_env_lst *list, char *data);
t_env		*env_def_initialize(void);
void		env_lst_print(t_env_lst *list);
void		exp_lst_print(t_env_lst *list);



//parsing.c
void		parsing(t_args *args);
void		cmd_expanded(t_cmd_lst *cmd_lst, t_args *args);
void		cmd_quote_clear(t_cmd_lst *cmd_lst);

//builtins.c
int			cmp_len(char *cleaned_del, char *s);
char		*before(char *s);
char		*equal_str(char *s);
int			cd(char *path, char **env, t_args *a);
int			ft_exit(t_cmd *cmd_head);
int			echo(t_cmd *cmd_node);
int			env(t_env_lst *env_lst, char *arg, char **envv);
int			pwd(void);
char		*adding_quotes(char *s);
char		*equality_out_of_quotes(char *s);
int			unset(t_env_lst *env_lst, t_env_lst *exp_lst, t_cmd *cmd_node);
int			error_checks_for_var(char *s, int until, int k);
int			until_equal_sign(char *s);

//exec_sum_up.c
char		*ft_strjoin3(char *str1, char *str2, char *str3);
void		dup_in_or_not_ttq(t_cmd *cur, int pipefd);
void		dup_out_or_not_ttq(t_cmd *cmd, int pipefd);
int			last_input_work(t_red_lst *red_lst);

//export.c
int			cmpfree(char *s1, char *s2, int f);
int			export_update(char *arg, char *arg_val, t_args *a);
t_env_lst	*exp_cpy_env(t_args *a);
int			ft_export(t_cmd *cmd, t_args *a);
void		export_pars(char *s, t_args *a);

//export_utils.c
int			find_unquoted(char *s);
char		*adding_quotes(char *s);
char		*equality_out_of_quotes(char *s);
void		sort(t_env_lst	*exp_lst);
t_env		*is_in_env_or_not(t_env_lst *env_lst, char *arg);
t_env		*is_in_exp_or_not(t_env_lst *exp_lst, char *arg);
int			is_in_export_or_not(char *arg, char *val, t_args *a);
//error
void		error_dup(int du);

//builtin_main.c
int			build(t_cmd *cmd, t_args *a);
//signal_handling.c
void		sig_handler_child(int sig);
void		ft_putendl_fd(char *s, int fd);
void		sig_control(int a);
void		sigint_handler(int sig);
void		sig_handler_hdoc(int sig);
void		sigquit_handler(int sig);

//utils2.c
int			last_pipe_check(char *s);
char		*ft_itoa(int n);
void		update_status(t_args *args);
void		remove_cur_env_node(t_env_lst *env_lst, char *s);
void		redirections(t_cmd_lst *lst);
//frees.c
void		free_get_del(char *del, char *get, int hdoc_flg);
void		pipefds_free(pid_t (*piefds)[2]);
void		env_lst_destruct(t_env_lst **list);
void		lst_destruct(t_list **list);
void		free_a(t_args *a);
void		dbl_free(char **arr);
void		cmd_def_free(t_cmd *node);
void		cmd_lst_destruct(t_cmd_lst **list, t_cmd *until);
void		printer(char **s);
void		update_free(t_cmd_lst **cmd_lst, t_list **lst, char *s, t_args *a);
void		ft_perror_and_exit(char *cmd, int code);
#endif
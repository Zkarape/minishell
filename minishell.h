/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:37:36 by zkarapet          #+#    #+#             */
/*   Updated: 2022/11/30 01:04:04 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_commands
{
	char	*redir;
	char	*command;
	char	**options;
	char	*join1;
	char	**splitted;
}	t_cmd;

typedef struct s_token
{
	char	*token;
	int		flag;
}	t_token;

//split_utils.c
//
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *b, int c, size_t len);
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);

//ft_split.c
//
int			ft_count(char const *s, char c);
char const	*ft_start(char const *s, char c);
char const	*ft_end(char const *s, char c);
int			ft_check_alloc(char **split, char *str, int index);
char		**ft_split(char const *s, char c);
//utils.c
char	*ft_strjoin(char const *s1, char const *s2);

# endif

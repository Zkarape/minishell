/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aivanyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:29:04 by aivanyan          #+#    #+#             */
/*   Updated: 2023/02/22 23:38:52 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	forking_separately(t_args *a, t_cmd *cur, int size)
{
	int	i;

	i = 0;
	a->size = size - 1;
	a->pids = malloc(sizeof(pid_t) * (size));
	if (size == 1)
		checking_fork(a, forking(cur->fd_in, cur->fd_out, cur, a), i - 1);
	else
	{
		checking_fork(a, forking(cur->fd_in, a->pipefds[0][1], cur, a), i - 1);
		cur = cur->next;
		while (cur->next)
		{
			checking_fork(a, forking(a->pipefds[i][0],
					a->pipefds[i + 1][1], cur, a), i);
			if (i < size - 2)
				i++;
			cur = cur->next;
		}
		checking_fork(a, forking(a->pipefds[i][0], cur->fd_out, cur, a), i);
		close_pipefds(a->pipefds, size - 1, NULL, 0);
	}
	return (0);
}

int	pipex_main(t_cmd_lst *cmd_lst, t_args *a)
{
	int		i;
	int		(*pipefds)[2];
	t_cmd	*cur;

	i = -1;
	cur = cmd_lst->head;
	a->cmd_lst_size = cmd_lst->size;
	if (!cur)
		return (1);
	if (cmd_lst->size == 1)
		pipefds = NULL;
	else
		pipefds = malloc(sizeof(int *) * (cmd_lst->size - 1));
	while (++i < cmd_lst->size - 1)
	{
		if (pipefds_check(pipefds, i, cur))
			return (1);
	}
	a->pipefds = pipefds;
	forking_separately(a, cur, cmd_lst->size);
	cur = cmd_lst->head;
	closing(cur);
	processing_status(a, cmd_lst->size);
	return (0);
}

pid_t	forking(int pipefd_in, int pipefd_out, t_cmd *cur, t_args *a)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		sig_control(0);
		process(pipefd_in, pipefd_out, cur, a);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (pid);
}

void	process(int pipefd_in, int pipefd_out, t_cmd *cmd, t_args *a)
{
	int	i;
	int	b;

	i = -1;
	b = 0;
//	if (red_big_loop(cmd))
//		ft_print_error_and_exit("file not found\n", 127);
	dup_in_or_not_ttq(cmd, pipefd_in);
	dup_out_or_not_ttq(cmd, pipefd_out);
	while (a->pipefds && ++i < a->size)
	{
		close(a->pipefds[i][0]);
		close(a->pipefds[i][1]);
	}
	close_in_out(cmd->fd_out);
	close_in_out(cmd->fd_in);
	close_in_out(cmd->hdoc_fd);
	if (!cmd->no_cmd[0])
		exit(1);
	b = build(cmd, a);
	if (!b)
		execute(cmd, a->env);
	else
		exit(g_status);
}

void	execute(t_cmd *cmd, char **env)
{
	char	*paths;
	char	**path;
	char	*absolue_path;
	int		i;

	i = 0;
	absolue_path = NULL;
	execve(cmd->no_cmd[0], cmd->no_cmd, env);
	paths = get_environment("PATH=", env);
	path = split(paths, ':');
	if (path)
	{
		while (path[i])
		{
			absolue_path = ft_strjoin3(path[i++], "/", cmd->no_cmd[0]);
			execve(absolue_path, cmd->no_cmd, env);
			free(absolue_path);
		}
	}
	ft_print_error_and_exit("cmd not found\n", 127);
}

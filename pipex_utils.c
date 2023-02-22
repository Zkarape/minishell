/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkarapet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:40:52 by zkarapet          #+#    #+#             */
/*   Updated: 2023/02/22 19:46:32 by zkarapet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checking_fork(t_args *a, pid_t forking, int i)
{
	int	j;

	j = -1;
	a->pids[i + 1] = forking;
	if (forking < 0)
	{
		while (a->pids[++j] != a->pids[i + 1])
			kill(a->pids[j], 0);
	}
}
// A process terminates normally when its program signals it is done by calling exit. Returning from main is equivalent to calling exit, and the value that main returns is used as the argument to exit. WIFEXITED(status) checks if child terminated normally, WEXITSTATUS(status) generates exit status of child, WTERMSIG(status) macro returns the numeric value of the signal that was raised by the child process

void	processing_status(t_args *a, int size)
{
	pid_t	pid;
	int		i;
	int		status;

	i = -1;
	status = 0;
	while (++i < size)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == a->pids[size - 1])
		{
			if (!WTERMSIG(status)) // child completed successfully
				g_status = WEXITSTATUS(status);
			else // terminated with failure
			{
				g_status = WTERMSIG(status) + 128;
				if (g_status == 130)
					write(1, "\n", 1);
				else if (g_status == 131)
					ft_putstr_fd("Quit 3", 1, 1);
			}
		}
	}
}

int	pipefds_check(int (*pipefds)[2], int i, t_cmd *cur)
{
	if (pipe_error(pipe(pipefds[i])))
	{
		close_pipefds(pipefds, i, cur, 1);
		pipefds_free(pipefds);
		return (1);
	}
	return (0);
}

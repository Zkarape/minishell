#include "minishell.h"

int	is_red(char c)
{
	return (c == '<' || c == '>');
}

char	*filename_trim(char *s, int k)
{
	int		i;
	char	*file;
	char	*file_trimmed;

	i = 0;
	if (k < 0)
		return (NULL);
	file = malloc(sizeof(char) * k + 1);
	while (s[i] && i < k)
	{
		file[i] = s[i];
		i++;
	}
	file[i] = '\0';
	//file_trimmed = file;
	//free(file);
	file = filling_with_nulls(file);
	printf("file == %s\n", file);
	return (file);
}

void	func_for_reds(t_cmd *cmd_node, t_red *red_node)
{
	int	fd_in;
	int	fd_out;

	if (cmd_node->fd_in != 0)
		close(cmd_node->fd_in);
	if (cmd_node->fd_out != 1)
		close(cmd_node->fd_out);
	if (red_node->type == INPUT_REDIRECTION)
		fd_out = open(red_node->file, O_RDONLY);
	else if (red_node->type == APPEND_REDIRECTION)
		fd_in = open(red_node->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (red_node->type == OUTPUT_REDIRECTION)
		fd_in = open(red_node->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_in < 0 || fd_out < 0)
		ft_print_error_and_exit("file not found'\n", EXIT_FAILURE);
	dup2(fd_in, cmd_node->fd_in);
	dup2(fd_out, cmd_node->fd_out);
}

void	red_big_loop(t_red_lst *red_lst, t_cmd *cmd)
{
	t_red	*cur;

	cur = red_lst->head;
	while (cur)
	{
		if (cur->type != HEREDOC)
			func_for_reds(cmd, cur);
		cur = cur->next;
	}
}

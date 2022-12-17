#include "minishell.h"

int main(int ac, char **av)
{
	int i;
	t_cmd	*cmd = cmd_node_initializer();
	t_list	*group = lst_construct();

	i = -1;
	char *s = readline("minishell$");
	group_until_pipe(s, group);
//	char **arr = ft_split(s);
//	char *cpy;
//	while (arr[++i])
//	{
//		printf("before %s\n", arr[i]);
//		cpy = strcpy_noquotes(arr[i], '"');
//		printf("after %s\n", cpy);
//	}
	func_for_reds(group->head->data, cmd);
	printf("in == %d out == %d\n", cmd->fd_in, cmd->fd_out);
}

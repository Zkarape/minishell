#include "minishell.h"

int	last_pipe_check(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0 && ft_is_space(s[i]))
		i--;
	if (i >= 0 && s[i] == '|')
		return (0);
	return (1);	
}

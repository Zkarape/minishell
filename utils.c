#include "minishell.h"

char	*str_return_trimmed(char *s, int start, int end)
{
	char	*dst;
	int		i;

	i = -1;
	dst = malloc(sizeof(char) * (ft_strlen(s) - end + start));
	printf("%d\n", ft_strlen(s) - end + start);
	while (++i < start)
		dst[i] = s[i];
	end++;
	while (s[end])
	{
		dst[i] = s[end];
		end++;
		i++;
	} 
	dst[i] = '\0';
	return (dst);
}

#include "minishell.h"

char	*cpy_with_cleaining(char *dst, char *src, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] && i < n)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	while (dst[j])
	{
		dst[j] = '\0';
		j++;
	}
	return (dst);
}

//int main()
//{
//	char **s = malloc(sizeof(char*) * 1);
//	char *s1 = malloc(sizeof(char) * 5);
//	int	i = -1;
//	while (++i < 2)
//	{
//		*s = malloc(sizeof(char) * 3);
//		s[0][0] = '"';
//		s[0][1] = '<';
//		s[0][2] = '"';
//	}
//	printf("%s\n", *s);
//	*s = cpy_with_cleaining(*s, "<", 1);
//	printf("%s\n", *s);
//}

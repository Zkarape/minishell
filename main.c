#include "minishell.h"

int main(int ac, char **av)
{
	//int i;

	//i = -1;
	//int i = -1;
	char *s = readline("minishell$");
	//printf("s is : %s\n", s);
	expand(s);
	//grouping_with_red(group_until_pipe(s));
	//char **arr = ft_split(s);
	//char *cpy;
	//while (arr[++i])
	//{
///	printf("sizeof %lu\n", sizeof(d)/sizeof(int));
	//	cpy = strcpy_noquotes(arr[i], '"');
	//	printf("after %s\n", cpy);
	//printf("%d",return_type('>', '>'));
}	

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *dst = malloc(sizeof(char) * 6000000);
	int i = -1;
	while (++i < 900000000)
	{
		dst[i] = 'h';
	}
	dst[i] = '\0';
	printf("%s\n", dst);
}

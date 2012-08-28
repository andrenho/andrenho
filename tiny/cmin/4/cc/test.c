#include <stdio.h>

unsigned char t()
{
	return 2000;
}


int main()
{
	unsigned int i = t();
	printf("%d\n", i);
	return 0;
}
